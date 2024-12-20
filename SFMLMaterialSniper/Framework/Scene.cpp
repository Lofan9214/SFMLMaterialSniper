#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	:id(id)
{
}

void Scene::Init()
{
	ApplyAddGo();
	ApplyRemoveGO();

	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyAddGo();
	ApplyRemoveGO();

	TEXTURE_MGR.UnloadAll();
	FONT_MGR.UnloadAll();
	SOUNDBUFFER_MGR.UnloadAll();
	ANIMATIONCLIP_MGR.UnloadAll();
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->Update(dt);
	}
}

void Scene::LateUpdate(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->LateUpdate(dt);
	}
}

void Scene::FixedUpdate(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->FixedUpdate(dt);
	}
}

void Scene::OnPreDraw()
{
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::stable_sort(worldViewObjects.rbegin(), worldViewObjects.rend(), DrawOrderComparer());
	std::stable_sort(uiViewObjects.rbegin(), uiViewObjects.rend(), DrawOrderComparer());

	const sf::View& previousView = window.getView();

	window.setView(worldView);

	for (auto obj : worldViewObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}
		obj->Draw(window);
	}

	window.setView(uiView);

	for (auto obj : uiViewObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}
		obj->Draw(window);
	}

	window.setView(previousView);
}

void Scene::OnPostDraw()
{
	ApplyAddGo();
	ApplyRemoveGO();
	if (GameObjectChanged)
	{
		GameObjectChanged = false;
		worldViewObjects.clear();
		uiViewObjects.clear();

		for (auto obj : gameObjects)
		{
			if (obj->GetSortingLayer() >= SortingLayers::UI)
			{
				uiViewObjects.push_back(obj);
			}
			else
			{
				worldViewObjects.push_back(obj);
			}
		}
	}
}

void Scene::RemoveGo(GameObject* obj)
{
	removeGameObjects.push_back(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	list.clear();
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			list.push_back(obj);
		}
	}
	return list.size();
}

void Scene::ApplyAddGo()
{
	GameObjectChanged = true;
	for (auto go : addGameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addGameObjects.clear();
}

void Scene::ApplyRemoveGO()
{
	GameObjectChanged = true;
	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f uiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPos, uiView);
}

sf::Vector2f Scene::WorldToUi(sf::Vector2f worldPos)
{
	return uiView.getInverseTransform().transformPoint(worldView.getTransform().transformPoint(worldPos));
}

sf::Vector2f Scene::UiToWorld(sf::Vector2f uiPos)
{
	return worldView.getInverseTransform().transformPoint(uiView.getTransform().transformPoint(uiPos));
}

sf::FloatRect Scene::WorldRegion()
{
	sf::FloatRect viewrect;
	sf::Vector2f size = worldView.getSize();
	sf::Vector2f center = worldView.getCenter();
	viewrect.left = center.x - size.x * 0.5f;
	viewrect.top = center.y - size.y * 0.5f;
	viewrect.width = size.x;
	viewrect.height = size.y;

	return viewrect;
}

void Scene::SetWorldView(unsigned int width, unsigned int height)
{
	float ratio = width * 1.f / height;
	float newwidth = 1080.f * ratio;

	worldView.setCenter(0.f,0.f);
	worldView.setSize(newwidth, 1080.f);
}
