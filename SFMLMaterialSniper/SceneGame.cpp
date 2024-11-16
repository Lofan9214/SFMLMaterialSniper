#include "stdafx.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "CircleView.h"
#include "Drum.h"
#include "RoundBoard.h"
#include "Bottle.h"
#include "UiHud.h"
#include "Player.h"
#include "GlassShard.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	SpriteGo* bg = AddGo(new SpriteGo("graphics/Stage1Background.jpg", "background"));

	bg->SetSortingLayer(SortingLayers::Background);
	bg->SetOrigin(Origins::MC);
	bullet = AddGo(new Bullet("bullet"));

	drum = AddGo(new Drum("drum"));
	roundBoard = AddGo(new RoundBoard("round"));
	bottle = AddGo(new Bottle("bottle"));

	uiHud = AddGo(new UiHud("uiHud"));

	scopeview = new CircleView(150.f, 5.f);
	player = AddGo(new Player("player"));
	player->SetCircleView(scopeview);

	Scene::Init();
}

void SceneGame::Enter()
{
	Scene::Enter();

	sf::Vector2f screensize = FRAMEWORK.GetWindowSizef();

	drum->SetPosition({ 300.f,0.f,700.f });
	roundBoard->SetPosition({ -300.f,0.f,700.f });
	bottle->SetPosition({ 0.f,0.f,700.f });

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);

}

void SceneGame::Exit()
{
	for (auto glassShard : glassShards)
	{
		RemoveGo(glassShard);
		glassShardPool.Return(glassShard);
	}
	glassShards.clear();

	delete scopeview;
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	uiHud->SetWind(wind);
	uiHud->SetAmmo(wind);
	uiHud->SetBreath(wind);
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		wind -= 1.f;
		bullet->SetWind({ wind,0.f,0.f });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		wind += 1.f;
		bullet->SetWind({ wind,0.f,0.f });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F5))
	{
		drum->Reset();
		roundBoard->Reset();
		bottle->Reset();
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	
	const sf::View& previousView = window.getView();

	window.setView(worldView);

	window.setView(previousView);
	scopeview->Draw(window, worldViewObjects);
}

GlassShard* SceneGame::TakeGlassShard()
{
	GlassShard* glassShard = glassShardPool.Take();
	glassShards.push_back(glassShard);
	AddGo(glassShard);
	return glassShard;
}

void SceneGame::ReturnGlassShard(GlassShard* glassShard)
{
	RemoveGo(glassShard);
	glassShardPool.Return(glassShard);
	glassShards.remove(glassShard);
}
