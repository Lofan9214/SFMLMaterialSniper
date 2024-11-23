#include "stdafx.h"
#include "SceneHome.h"
#include "UiBullet.h"
#include "UiSkill.h"
#include "ButtonRound.h"

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

	btnGameStart = AddGo(new ButtonRound("gamestart"));

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

	uiBullet->SetPosition({ screensize.x * 0.05f ,screensize.y * 0.3f });
	uiSkill->SetPosition({ screensize.x * 0.34375f ,screensize.y * 0.3f });

	btnGameStart->SetPosition({ screensize.x * 0.5f ,screensize.y * 0.9f });
	btnGameStart->SetScale({ 2.f, 2.f });
	btnGameStart->SetCharSize(55.f);
	btnGameStart->SetString("Start", true);
	btnGameStart->SetClicked([]() {SCENE_MGR.ChangeScene(SceneIds::Game); });

	Scene::Enter();
	SOUND_MGR.PlayBgm("sounds/bgm/home.mp3");

}

void SceneHome::Exit()
{
	Scene::Exit();
	SAVEDATA_MGR.Save();
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
