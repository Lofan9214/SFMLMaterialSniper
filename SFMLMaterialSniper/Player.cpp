#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "CircleView.h"
#include "Gun.h"

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
	sortingOrder = 150;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.Play("animations/player/playeridle.csv");

	animator.AddEvent("playerfire", 8, [this]()
		{
			SOUND_MGR.PlaySfx("sounds/player/boltaction.mp3");
			if (gun != nullptr)
			{
				gun->NextRoad();
			}
		});
	animator.AddEvent("playerreloadend", 2, [this]()
		{
			SOUND_MGR.PlaySfx("sounds/player/boltaction.mp3");
		});
	animator.AddEvent("playerfire", 21, [this]()
		{
			SetStatus(Status::Ready);
		});
}

void Player::Release()
{
	auto& savedata = SAVEDATA_MGR.Get();
	savedata.skillData = skillData;
	SAVEDATA_MGR.Save();
}

void Player::Reset()
{
	breathover = false;

	auto screensize = FRAMEWORK.GetDefaultSize();
	SetScale({ 1.5f,1.5f });
	SetPosition({ -screensize.x * 0.5f - 150.f, screensize.y * 0.5f + 130.f });
	SetOrigin(Origins::BL);

	gun = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		gun = dynamic_cast<Gun*>(scene->FindGo("gun"));
	}

	skillData = SAVEDATA_MGR.Load().skillData;
	maxBreath = 2.7f + skillData.control * 0.3f;
	magazine = 5 + skillData.magazine;

	breath = maxBreath;
	ammo = magazine;

	if (gun != nullptr)
	{
		gun->SetScope(skillData.scopeSize);
		gun->SetRecoilSpeed(skillData.stablility);
	}

	SetStatus(Status::Ready);
}

void Player::Update(float dt)
{
	animator.Update(dt);

	UpdateBreathStatus(dt);

	switch (status)
	{
	case Player::Status::Ready:
		UpdateReady(dt);
		break;
	case Player::Status::Fire:
		UpdateFire(dt);
		break;
	case Player::Status::Reloading:
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
			--ammo;

			animator.Play("animations/player/playerfire.csv");
			animator.PlayQueue("animations/player/playeridle.csv");

			gun->Fire();

			SetStatus(Status::Fire);
		}
		else
		{
			//Todo 재장전 알림 만들어야 함
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Z)
		|| InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		ammo = 0;
		reloadTimer = 0.f;
		SetStatus(Status::Reloading);
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
		SOUND_MGR.PlaySfx("sounds/player/endreload.mp3");
		animator.Play("animations/player/playerreloadend.csv");
		animator.PlayQueue("animations/player/playeridle.csv");
	}
	if (reloadTimer > reloadDuration)
	{
		SetStatus(Status::Ready);
		ammo = magazine;
	}
}

void Player::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(body);
}

void Player::SetStatus(Status status)
{
	Status prev = this->status;
	this->status = status;
	switch (status)
	{
	case Player::Status::Ready:
		break;
	case Player::Status::Fire:
		break;
	case Player::Status::Reloading:
		animator.Play("animations/player/playerreloadstart.csv");
		SOUND_MGR.PlaySfx("sounds/player/startreload.mp3");
		break;
	}
}

void Player::UpdateBreathStatus(float dt)
{
	if (breathover)
	{
		breath = Utils::Clamp(breath + dt * 0.5f, 0.f, maxBreath);
		if (breath == maxBreath)
		{
			breathover = false;
			gun->SetBreathover(false);
			gun->SetVibrationSpeed(1.f);
		}
		return;
	}

	if (InputMgr::GetKeyPressing(sf::Keyboard::Space))
	{
		if (breath == 0.f)
		{
			gun->SetVibrationSpeed(3.f);
			breathover = true;
		}
		else
		{
			gun->SetVibrationSpeed(0.5f);
		}
		breath = Utils::Clamp(breath - dt, 0.f, maxBreath);
	}
	else
	{
		breath = Utils::Clamp(breath + dt * 0.5f, 0.f, maxBreath);
	}
}
