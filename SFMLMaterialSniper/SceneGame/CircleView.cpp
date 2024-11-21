#include "stdafx.h"
#include "CircleView.h"
#include "Scene.h"

CircleView::CircleView(const std::string& name)
	:GameObject(name)
{
}

void CircleView::SetCircleRadius(float radius)
{
	maskRadius = radius;
	rendermask.setRadius(maskRadius);
	Utils::SetOrigin(rendermask, Origins::MC);
	float diameter = maskRadius * 2.f;
	renderTexture.create(diameter, diameter);
	renderView.reset({ 0.f,0.f ,diameter,diameter });
	renderView.zoom(1.f / zoom);

	bodytube.setScale({ diameter / 150.f ,diameter / 150.f });
	crosshairh.setSize({ diameter * 0.8f,3.f });
	crosshairv.setSize({ 3.f,diameter * 0.8f });
	SetOrigin(Origins::MC);
}

void CircleView::SetZoom(float zoom)
{
	this->zoom = zoom;

	float zoomfactor = 1.f / this->zoom;
	renderView.zoom(zoomfactor);

	crosshairh.setFillColor(sf::Color::Black);
	crosshairv.setFillColor(sf::Color::Black);
}

void CircleView::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(crosshairv, originPreset);
	Utils::SetOrigin(crosshairh, originPreset);
	Utils::SetOrigin(bodytube, originPreset);
	Utils::SetOrigin(noScope, originPreset);
}

void CircleView::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	renderView.setCenter(position);
}

void CircleView::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = (int)GameDefine::SortingOrders::CircleView;
}

void CircleView::Release()
{
}

void CircleView::Reset()
{
	bodytube.setTexture(TEXTURE_MGR.Get(bodytubeTexId));
	noScope.setTexture(TEXTURE_MGR.Get(noScopeTexId));
}

void CircleView::Update(float dt)
{
	useScope = !InputMgr::GetKeyPressing(sf::Keyboard::LShift);
}

void CircleView::LateUpdate(float dt)
{
	if (!useScope)
	{
		noScope.setPosition(SCENE_MGR.GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition()));
		return;
	}

	rendermask.setPosition(position);
	bodytube.setPosition(position);
	crosshairh.setPosition(position);
	crosshairv.setPosition(position);

	renderTexture.clear();
	renderTexture.setView(renderView);
	std::list<GameObject*> lstobject = SCENE_MGR.GetCurrentScene()->GetWorldGameObjects();
	for (auto obj : lstobject)
	{
		if (!obj->IsActive() || obj->GetSortingOrder() > 0 || obj == this)
		{
			continue;
		}
		obj->Draw(renderTexture);
	}
	renderTexture.display();
	renderTexture.setSmooth(true);
	rendermask.setTexture(&renderTexture.getTexture());
}

void CircleView::Draw(sf::RenderTarget& window)
{
	if (useScope)
	{
		window.draw(rendermask);
		window.draw(crosshairv);
		window.draw(crosshairh);
		window.draw(bodytube);
	}
	else
	{
		window.draw(noScope);
	}
}
