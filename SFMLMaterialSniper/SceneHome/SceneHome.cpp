#include "stdafx.h"
#include "SceneHome.h"
#include "UiBullet.h"
#include "UiSkill.h"

SceneHome::SceneHome() : Scene(SceneIds::Home)
{
}

void SceneHome::Init()
{
	SpriteGo* bg = AddGo(new SpriteGo("graphics/home/dorm.png", "background"));

	bg->SetSortingLayer(SortingLayers::Background);
	bg->SetOrigin(Origins::MC);

	uiBullet = AddGo(new UiBullet("uibullet"));

	uiSkill = AddGo(new UiSkill("uiskill"));

	Scene::Init();
}

void SceneHome::Release()
{
	Scene::Release();
	SAVEDATA_MGR.Save();
}

void SceneHome::Enter()
{
	sf::Vector2f screensize = FRAMEWORK.GetDefaultSize();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);

	uiBullet->SetPosition({ screensize.x * 0.1f ,screensize.y * 0.4f });
	uiSkill->SetPosition({ screensize.x * 0.5f ,screensize.y * 0.4f });

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
