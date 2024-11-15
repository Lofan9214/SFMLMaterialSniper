#include "stdafx.h"
#include "SceneGame.h"
#include "UiScore.h"
#include "UiMessage.h"
#include "SpriteGo.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	bg = AddGo(new SpriteGo("bg.jpg", "name"));
	//bg->SetActive(false);
	uiScore = AddGo(new UiScore("fonts/KOMIKAP_.ttf"));
	uiMessage = AddGo(new UiMessage("fonts/KOMIKAP_.ttf"));
	minimap = sf::CircleShape(50.f);
	auto size = FRAMEWORK.GetWindowSizef();

	uiScore->SetPosition({ size.x * 0.5f, 100.f });
	uiMessage->SetPosition({ size.x * 0.5f, size.y * 0.5f });

	Scene::Init();
}

void SceneGame::Enter()
{
	TEXTURE_MGR.Load("bg.jpg");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	FRAMEWORK.SetTimeScale(1.f);

	sf::Vector2f size = FRAMEWORK.GetWindowSizef();

	worldView.setSize(size);
	worldView.setCenter(size*0.5f);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();

	isBallFired = false;
}

void SceneGame::Exit()
{
	TEXTURE_MGR.Unload("bg.jpg");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
