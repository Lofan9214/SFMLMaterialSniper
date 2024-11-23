#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "CircleView.h"
#include "BulletShell.h"
#include "Gun.h"
#include "UiHud.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = (int)GameDefine::SortingOrders::Player;

	animator.SetSprite(&body);
	animator.BindFunction(this);

	animator.AddEvent("playerfire", 6, [this]()
		{
			if (gun != nullptr)
			{
				gun->SetRecoilStatus(GameDefine::RecoilStatus::BoltPulling);
			}
		});

	animator.AddEvent("playerfire", 10, [this]()
		{
			SOUND_MGR.PlaySfx("sounds/player/boltaction.mp3");
			if (TakeBulletShell)
			{
				BulletShell* bulletShell = TakeBulletShell();
				bulletShell->Eject(body.getTransform().transformPoint(ejectionPos));
			}
		});
	animator.AddEvent("playerfire", 34, [this]()
		{
			//std::cout << "fireready" << std::endl;
			SetStatus(PlayerStatus::Ready);
		});
	animator.AddEvent("playerreloadend", 2, [this]()
		{
			SOUND_MGR.PlaySfx("sounds/player/boltaction.mp3");
		});
}

void Player::Release()
{
	auto& savedata = SAVEDATA_MGR.Get();
	savedata.skillData = skillData;
	SAVEDATA_MGR.Save();
	animator.Pause();
}

void Player::Reset()
{
	animator.Play("animations/player/playeridle.csv");
	ANIMATIONCLIP_MGR.Load("animations/player/playerfire.csv");
	ANIMATIONCLIP_MGR.Load("animations/player/playerreloadend.csv");
	ANIMATIONCLIP_MGR.Load("animations/player/playerreloadstart.csv");

	auto screensize = FRAMEWORK.GetDefaultSize();
	SetScale({ 0.375f,0.375f });
	SetPosition({ -screensize.x * 0.5f - 150.f, screensize.y * 0.5f + 130.f });
	SetOrigin(Origins::BL);

	gun = nullptr;
	uiHud = nullptr;
	TakeBulletShell = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		gun = dynamic_cast<Gun*>(scene->FindGo("gun"));
		uiHud = dynamic_cast<UiHud*>(scene->FindGo("uiHud"));
		TakeBulletShell = [scene]() {return scene->TakeBulletShell(); };
	}

	skillData = SAVEDATA_MGR.Load().skillData;
	maxBreath = 2.7f + skillData.control * 0.3f;
	magazine = 5 + skillData.magazine;

	breath = maxBreath;
	ammo = magazine;

	if (gun != nullptr)
	{
		gun->SetScope(skillData.scopeSize);
		gun->SetRecoilScale(skillData.stablility);
	}

	breathStatus = GameDefine::BreathStatus::Normal;
	playerStatus = PlayerStatus::Wait;
}

void Player::Update(float dt)
{
	animator.Update(dt);

	UpdateBreathStatus(dt);

	switch (playerStatus)
	{
	case Player::PlayerStatus::Ready:
		UpdateReady(dt);
		break;
	case Player::PlayerStatus::Fire:
		UpdateFire(dt);
		break;
	case Player::PlayerStatus::Reloading:
		UpdateReload(dt);
		break;
	}
}

void Player::UpdateReady(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (ammo > 0)
		{
			SetStatus(PlayerStatus::Fire);
		}
		else
		{
			uiHud->SetReloadActive(true);
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Z)
		|| InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		uiHud->SetReloadActive(false);
		SetStatus(PlayerStatus::Reloading);
	}
}

void Player::UpdateFire(float dt)
{
}

void Player::UpdateReload(float dt)
{
	reloadTimer += dt;
	float reloadDuration = 100.f / (24.f * (3.f + skillData.reload));
	if (reloadTimer > reloadDuration - 0.5f
		&& animator.GetCurrentClipId() == "playerreloadstart")
	{
		if (uiHud != nullptr)
		{
			uiHud->SetAmmo(magazine);
			uiHud->SetReloadStatus(UiHud::ReloadStatus::MagazineInserted);
		}
		SOUND_MGR.PlaySfx("sounds/player/endreload.mp3");
		animator.Play("animations/player/playerreloadend.csv");
		animator.PlayQueue("animations/player/playeridle.csv");
	}
	if (reloadTimer > reloadDuration)
	{
		ammo = magazine;
		SetStatus(PlayerStatus::Ready);
	}
}

void Player::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(body);
}

void Player::SetStatus(PlayerStatus status)
{
	PlayerStatus prev = playerStatus;
	playerStatus = status;

	switch (status)
	{
	case Player::PlayerStatus::Wait:
		break;
	case Player::PlayerStatus::Ready:
		if (prev == PlayerStatus::Reloading && reloadTimer < 100.f / (24.f * (3.f + skillData.reload)))
		{
			std::cout << "sf" << std::endl;

			playerStatus = prev;
		}
		break;
	case Player::PlayerStatus::Fire:
		--ammo;
		animator.Play("animations/player/playerfire.csv");
		animator.PlayQueue("animations/player/playeridle.csv");
		gun->Fire();
		break;
	case Player::PlayerStatus::Reloading:
		ammo = 0;
		reloadTimer = 0.f;
		if (uiHud != nullptr)
		{
			uiHud->SetReloadStatus(UiHud::ReloadStatus::MagazineEjecting);
		}
		animator.Play("animations/player/playerreloadstart.csv");
		SOUND_MGR.PlaySfx("sounds/player/startreload.mp3");
		break;
	}
}

void Player::UpdateBreathStatus(float dt)
{
	switch (breathStatus)
	{
	case GameDefine::BreathStatus::Normal:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			SOUND_MGR.PlaySfx("sounds/player/breathstop.mp3");
			breathStatus = GameDefine::BreathStatus::Hold;
			gun->SetBreathStatus(breathStatus);
		}
		else
		{
			breath = Utils::Clamp(breath + dt * 0.5f, 0.f, maxBreath);
		}
		break;
	case GameDefine::BreathStatus::Hold:
		if (InputMgr::GetKeyUp(sf::Keyboard::Space))
		{
			breathStatus = GameDefine::BreathStatus::Normal;
			gun->SetBreathStatus(breathStatus);
		}
		else
		{
			breath = Utils::Clamp(breath - dt, 0.f, maxBreath);
			if (breath == 0.f)
			{
				breathStatus = GameDefine::BreathStatus::Over;
				gun->SetBreathStatus(breathStatus);
				SOUND_MGR.PlaySfx("sounds/player/breathover.mp3");
			}
		}
		break;
	case GameDefine::BreathStatus::Over:
		breath = Utils::Clamp(breath + dt * 0.5f, 0.f, maxBreath);
		if (breath == maxBreath)
		{
			breathStatus = GameDefine::BreathStatus::Normal;
			gun->SetBreathStatus(breathStatus);
		}
		break;
	}
}
