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
#include "Gun.h";
#include "BulletShell.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	SpriteGo* bg = AddGo(new SpriteGo("graphics/Stage1Background.png", "background"));

	bg->SetSortingLayer(SortingLayers::Background);
	bg->SetOrigin(Origins::MC);

	uiHud = AddGo(new UiHud("uiHud"));

	scopeview = AddGo(new CircleView("circleView"));
	gun = AddGo(new Gun("gun"));
	player = AddGo(new Player("player"));

	Scene::Init();
}

void SceneGame::Enter()
{
	Scene::Enter();
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	SOUND_MGR.PlayBgm("sounds/bgm/stage01.mp3");

	currentStatus = Status::Awake;

	sf::Vector2f screensize = FRAMEWORK.GetDefaultSize();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);

	uiHud->SetWind(wind);
	uiHud->SetAmmo(player->GetAmmo());
	uiHud->SetBreath(player->GetBreath());

	stage = 1;
	difficulty = 1;
	wave = 0;
	remains = 0;
	day = true;

	screenRecoilTimer = 1000.f;
}

void SceneGame::Exit()
{
	ClearTookObject();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	uiHud->SetWind(wind);
	uiHud->SetBreath(player->GetBreath());

	UpdateScreenRecoil(dt);

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneGame::Status::InGame:
		UpdateInGame(dt);
		break;
	case SceneGame::Status::Interlude:
		UpdateInterlude(dt);
		break;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F9))
	{
		Variables::isDrawHitBox = !Variables::isDrawHitBox;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(Status status)
{
	Status prev = currentStatus;
	currentStatus = status;

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		stage = 1;
		difficulty = 1;
		wave = 0;
		remains = 0;
		break;
	case SceneGame::Status::InGame:
		SpawnWave();
		break;
	case SceneGame::Status::Interlude:
		interludeTimer = 0.f;
		break;
	case SceneGame::Status::Result:
		SOUND_MGR.PlayBgm("sounds/bgm/stageclear.mp3");
		break;
	}
}

void SceneGame::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::InGame);
	}
}

void SceneGame::UpdateInGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		wind -= 1.f;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		wind += 1.f;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		ClearTookObject();
		SetStatus(Status::Awake);
	}
	if (remains == 0)
	{
		std::string stagestr = std::to_string(stage) + std::to_string(difficulty) + (day ? "D" : "N");
		const auto& dataStage = STAGE_TABLE->Get(stagestr);

		if (++wave == dataStage.waves.size())
		{
			SetStatus(Status::Result);
		}
		else
		{
			SetStatus(Status::Interlude);
		}
	}
}

void SceneGame::UpdateInterlude(float dt)
{
	interludeTimer += dt;
	if (interludeTimer > 3.f)
	{
		SetStatus(Status::InGame);
	}
}

void SceneGame::UpdateScreenRecoil(float dt)
{
	screenRecoilTimer += dt;
	screenRecoil = 270.f * sinf(screenRecoilTimer * Utils::PI * 3.f) * std::exp(screenRecoilTimer * -4.f);
	if (screenRecoilTimer > 0.f && screenRecoilTimer < 3.f)
	{
		worldView.setCenter({ screenRecoil, 0.f });
	}
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

Bullet* SceneGame::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bullets.push_back(bullet);
	AddGo(bullet);
	bullet->SetWind({ wind,0.f,0.f });
	return bullet;
}

void SceneGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bullets.remove(bullet);
}

BulletShell* SceneGame::TakeBulletShell()
{
	BulletShell* bulletShell = bulletShellPool.Take();
	bulletShells.push_back(bulletShell);
	AddGo(bulletShell);
	return bulletShell;
}

void SceneGame::ReturnBulletShell(BulletShell* bulletShell)
{
	RemoveGo(bulletShell);
	bulletShellPool.Return(bulletShell);
	bulletShells.remove(bulletShell);
}

void SceneGame::ClearTookObject()
{
	for (auto glassShard : glassShards)
	{
		RemoveGo(glassShard);
		glassShardPool.Return(glassShard);
	}
	glassShards.clear();

	for (auto drum : drums)
	{
		RemoveGo(drum);
		drumPool.Return(drum);
	}
	drums.clear();

	for (auto bottle : bottles)
	{
		RemoveGo(bottle);
		bottlePool.Return(bottle);
	}
	bottles.clear();

	for (auto roundboard : roundboards)
	{
		RemoveGo(roundboard);
		roundboardPool.Return(roundboard);
	}
	roundboards.clear();

	for (auto bulletShell : bulletShells)
	{
		RemoveGo(bulletShell);
		bulletShellPool.Return(bulletShell);
	}
	bulletShells.clear();

	for (auto bullet : bullets)
	{
		RemoveGo(bullet);
		bulletPool.Return(bullet);
	}
	bullets.clear();
}

void SceneGame::SpawnWave()
{
	std::string stagestr = std::to_string(stage) + std::to_string(difficulty) + (day ? "D" : "N");
	const auto& dataStage = STAGE_TABLE->Get(stagestr);

	auto find = dataStage.waves.find(wave);
	if (find == dataStage.waves.end())
	{
		return;
	}
	for (auto& datum : find->second)
	{
		++remains;
		if (datum.type == "DRUM")
		{
			SpawnDrum(datum.position);
		}
		else if (datum.type == "BOTTLE")
		{
			SpawnBottle(datum.position);
		}
		else if (datum.type == "ROUNDBOARD")
		{
			SpawnRoundBoard(datum.position);
		}
	}
}

void SceneGame::SpawnDrum(const sf::Vector3f& pos)
{
	Drum* drum = drumPool.Take();
	drums.push_back(drum);
	AddGo(drum);
	drum->SetPosition(pos);
}

void SceneGame::SpawnBottle(const sf::Vector3f& pos)
{
	Bottle* bottle = bottlePool.Take();
	bottles.push_back(bottle);
	AddGo(bottle);
	bottle->SetPosition(pos);
}

void SceneGame::SpawnRoundBoard(const sf::Vector3f& pos)
{
	RoundBoard* roundboard = roundboardPool.Take();
	roundboards.push_back(roundboard);
	AddGo(roundboard);
	roundboard->SetPosition(pos);
}
