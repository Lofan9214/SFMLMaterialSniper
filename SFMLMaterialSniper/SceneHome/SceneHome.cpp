#include "stdafx.h"
#include "SceneHome.h"


SceneHome::SceneHome() : Scene(SceneIds::Home)
{
}

void SceneHome::Init()
{
	SpriteGo* bg = AddGo(new SpriteGo("graphics/home/dorm.png", "background"));

	bg->SetSortingLayer(SortingLayers::Background);
	bg->SetOrigin(Origins::MC);

	Scene::Init();
}

void SceneHome::Release()
{
	Scene::Release();
}

void SceneHome::Enter()
{
	sf::Vector2f screensize = FRAMEWORK.GetDefaultSize();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);
	Scene::Enter();
}

void SceneHome::Exit()
{
	Scene::Exit();
}

void SceneHome::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneHome::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
