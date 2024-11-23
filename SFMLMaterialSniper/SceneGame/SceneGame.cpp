#include "stdafx.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "CircleView.h"
#include "Drum.h"
#include "RoundBoard.h"
#include "Bottle.h"
#include "Player.h"
#include "GlassShard.h"
#include "Gun.h";
#include "BulletShell.h"
#include "UiHud.h"
#include "UiResult.h"
#include "ButtonRound.h"
#include "WindController.h"
#include "ShootMark.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	SpriteGo* bg = AddGo(new SpriteGo("graphics/Stage1Background.png", "background"));

	bg->SetSortingLayer(SortingLayers::Background);
	bg->SetOrigin(Origins::MC);
	bg->SetScale({ 0.4f,0.4f });

	uiHud = AddGo(new UiHud("uiHud"));
	uiResult = AddGo(new UiResult("uiResult"));

	scopeview = AddGo(new CircleView("circleView"));
	gun = AddGo(new Gun("gun"));
	player = AddGo(new Player("player"));

	windController = AddGo(new WindController("windController"));

	for (int i = 0; i < 10; ++i)
	{
		shootmarks.push_back(AddGo(new ShootMark("shootMark")));
	}

	stage = -1;
	difficulty = -1;

	Scene::Init();
}

void SceneGame::Enter()
{
	Scene::Enter();

	bulletPool.Return(bulletPool.Take());
	glassShardPool.Return(glassShardPool.Take());
	bulletShellPool.Return(bulletShellPool.Take());
	bottlePool.Return(bottlePool.Take());
	drumPool.Return(drumPool.Take());
	roundboardPool.Return(roundboardPool.Take());

	currentStatus = GameDefine::SceneStatus::Awake;

	sf::Vector2f screensize = FRAMEWORK.GetDefaultSize();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);

	uiHud->SetWind(wind);
	uiHud->SetAmmo(player->GetAmmo());
	uiHud->SetBreath(player->GetBreath());

	screenRecoilTimer = 1000.f;

	SetStatus(GameDefine::SceneStatus::Awake);
}

void SceneGame::Exit()
{
	ClearTookObject();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	uiHud->SetBreath(player->GetBreath());

	UpdateScreenRecoil(dt);

	switch (currentStatus)
	{
	case GameDefine::SceneStatus::Awake:
		UpdateAwake(dt);
		break;
	case GameDefine::SceneStatus::InGame:
		UpdateInGame(dt);
		break;
	case GameDefine::SceneStatus::Interlude:
		UpdateInterlude(dt);
		break;
	case GameDefine::SceneStatus::Result:
		UpdateResult(dt);
		break;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		SetWind(--wind);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		SetWind(++wind);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Home);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		if (currentStatus != GameDefine::SceneStatus::Result)
		{
			SetStatus(GameDefine::SceneStatus::Result);
		}
		else
		{
			SetStatus(GameDefine::SceneStatus::Awake);
		}
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

void SceneGame::SetStatus(GameDefine::SceneStatus status)
{
	GameDefine::SceneStatus prev = currentStatus;
	currentStatus = status;

	windController->SetSceneStatus(currentStatus);

	switch (currentStatus)
	{
	case GameDefine::SceneStatus::Awake:
		if (prev == GameDefine::SceneStatus::Result)
		{
			uiResult->SetActive(false);
		}
		SOUND_MGR.PlayBgm("sounds/bgm/stage01.mp3");

		if (stage == -1)
		{
			stage = 1;
		}
		if (difficulty == -1)
		{
			difficulty = 1;
		}
		wave = 0;
		remains = 0;
		day = true;

		dataStage = STAGE_TABLE->Get(stage);
		windController->SetActive(true);

		break;
	case GameDefine::SceneStatus::InGame:
		if (prev == GameDefine::SceneStatus::Awake)
		{
			FRAMEWORK.GetWindow().setMouseCursorVisible(false);
			player->SetStatus(Player::PlayerStatus::Ready);
			windController->SetDifficulty(difficulty);
		}
		if (stage == 1)
		{
			if (wave == 0)
			{
				uiHud->SetFireActive(true, 3.f);
			}
			else if (wave == 1)
			{
				uiHud->SetSpaceActive(true, 3.f);
			}
		}
		SpawnWave();
		break;
	case GameDefine::SceneStatus::Interlude:
		interludeTimer = 0.f;
		break;
	case GameDefine::SceneStatus::Result:
		FRAMEWORK.GetWindow().setMouseCursorVisible(true);
		SOUND_MGR.PlayBgm("sounds/bgm/stageclear.mp3");
		player->SetStatus(Player::PlayerStatus::Wait);
		uiResult->ShowResult();
		uiResult->SetActive(true);
		windController->SetActive(false);
		break;
	}
}

void SceneGame::UpdateAwake(float dt)
{
	interludeTimer += dt;
	if (interludeTimer > 5.f)
	{
		SetStatus(GameDefine::SceneStatus::InGame);
	}
}

void SceneGame::UpdateInGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		ClearTookObject();
		SetStatus(GameDefine::SceneStatus::Awake);
	}
	if (remains == 0)
	{
		if (++wave == dataStage.waves.size())
		{
			SetStatus(GameDefine::SceneStatus::Result);
			SAVEDATA_MGR.Get().skillData.skillPoint += 10;
		}
		else
		{
			SetStatus(GameDefine::SceneStatus::Interlude);
		}
	}
}

void SceneGame::UpdateInterlude(float dt)
{
	interludeTimer += dt;
	if (interludeTimer > 3.f)
	{
		SetStatus(GameDefine::SceneStatus::InGame);
	}
}

void SceneGame::UpdateResult(float dt)
{
}

void SceneGame::UpdateScreenRecoil(float dt)
{
	screenRecoilTimer += dt;
	if (screenRecoilTimer > 0.f && screenRecoilTimer < 1.7f)
	{
		screenRecoil = 1500.f * sinf(std::powf(screenRecoilTimer, 0.75f) * Utils::PI * 2.f * 1.f) * std::exp((screenRecoilTimer + 1.f) * -2.f);
		worldView.setCenter({ screenRecoil, 0.f });
	}
	else
	{
		worldView.setCenter({ 0.f, 0.f });
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
	glassShards.remove(glassShard);
	glassShardPool.Return(glassShard);
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
	bullets.remove(bullet);
	bulletPool.Return(bullet);
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
	bulletShells.remove(bulletShell);
	bulletShellPool.Return(bulletShell);
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

	shootmarks.clear();
}

void SceneGame::SpawnWave()
{
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
	for (auto shootMark : shootmarks)
	{
		if (!shootMark->IsActive())
		{
			shootMark->SetPosition({ pos.x,100.f - FRAMEWORK.GetDefaultSize().y * 0.5f });

			shootMark->SetActive(true);
			drum->SetShootMark(shootMark);
			break;
		}
	}
}

void SceneGame::SpawnBottle(const sf::Vector3f& pos)
{
	Bottle* bottle = bottlePool.Take();
	bottles.push_back(bottle);
	AddGo(bottle);
	bottle->SetPosition(pos);
	for (auto shootMark : shootmarks)
	{
		if (!shootMark->IsActive())
		{
			shootMark->SetPosition({ pos.x,100.f - FRAMEWORK.GetDefaultSize().y * 0.5f });
			shootMark->SetActive(true);
			bottle->SetShootMark(shootMark);
			break;
		}
	}
}

void SceneGame::SpawnRoundBoard(const sf::Vector3f& pos)
{
	RoundBoard* roundboard = roundboardPool.Take();
	roundboards.push_back(roundboard);
	AddGo(roundboard);
	roundboard->SetPosition(pos);
	roundboard->SetAnimationScale({ 0.f,0.f });
	for (auto shootMark : shootmarks)
	{
		if (!shootMark->IsActive())
		{
			shootMark->SetPosition({ pos.x,100.f - FRAMEWORK.GetDefaultSize().y * 0.5f });
			shootMark->SetActive(true);
			roundboard->SetShootMark(shootMark);
			break;
		}
	}
}

void SceneGame::ReturnDrum(Drum* drum)
{
	drum->SetActiveShootMark(false);
	RemoveGo(drum);
	drums.remove(drum);
	drumPool.Return(drum);
}

void SceneGame::ReturnBottle(Bottle* bottle)
{
	bottle->SetActiveShootMark(false);
	RemoveGo(bottle);
	bottles.remove(bottle);
	bottlePool.Return(bottle);
}

void SceneGame::ReturnRoundBoard(RoundBoard* roundboard)
{
	roundboard->SetActiveShootMark(false);
	RemoveGo(roundboard);
	roundboards.remove(roundboard);
	roundboardPool.Return(roundboard);
}

void SceneGame::SetStage(int stage, int diff, bool day)
{
	this->stage = stage;
	this->difficulty = diff;
	this->day = day;
}

void SceneGame::SetWind(int speed)
{
	wind = speed;
	uiHud->SetWind(wind);
}
