#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "CircleView.h"

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
	sortingOrder = 300;

	bullet = dynamic_cast<Bullet*>(SCENE_MGR.GetCurrentScene()->FindGo("bullet"));
	vibrationScale.x = 20.f;
	vibrationScale.y = 30.f;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.Play("animations/player/playeridle.csv");

	animator.AddEvent("playerfire", 8, [this]()
		{
			SOUND_MGR.PlaySfx("sounds/player/boltaction.mp3");
			float rand = Utils::RandomRange(Utils::PI * 1.75f, Utils::PI * 1.85f);
			scopeRecoilVel.x += cosf(rand) * boltrecoilSpeed;
			scopeRecoilVel.y += sinf(rand) * boltrecoilSpeed;
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
	vibrationTimer = 0.f;
	breathover = false;

	auto screensize = FRAMEWORK.GetWindowSizef();
	SetPosition({ screensize.x * -0.5f, screensize.y * 0.5f });
	SetOrigin(Origins::BL);

	circleView = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		circleView = dynamic_cast<CircleView*>(SCENE_MGR.GetCurrentScene()->FindGo("circleView"));
	}

	skillData = SAVEDATA_MGR.Load().skillData;
	maxBreath = 2.7f + skillData.control * 0.3f;
	magazine = 5 + skillData.magazine;

	if (circleView != nullptr)
	{
		circleView->SetZoom(5.f);
		circleView->SetCircleRadius(150.f + skillData.scopeSize * 15.f);
	}
	recoilSpeed = (1.f - skillData.control * 0.1f) * 1700.f;
	boltrecoilSpeed = (1.f - skillData.control * 0.1f) * 1000.f;
	breath = maxBreath;
	ammo = magazine;
	SetStatus(Status::Ready);
}

void Player::Update(float dt)
{
	animator.Update(dt);

	UpdateScopePosition(dt);
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
			SOUND_MGR.PlaySfx("sounds/bullet/bulletfire1.mp3");
			bullet->Reset();
			bullet->SetPosition({ scopePos.x, scopePos.y, 0.f });
			bullet->Fire(bullet->GetPosition3());

			animator.Play("animations/player/playerfire.csv");
			animator.PlayQueue("animations/player/playeridle.csv");

			float rand = Utils::RandomRange(Utils::PI * 1.35f, Utils::PI * 1.40f);
			scopeRecoilVel.x = cosf(rand) * recoilSpeed;
			scopeRecoilVel.y = sinf(rand) * recoilSpeed;
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

void Player::UpdateScopePosition(float dt)
{
	if (circleView == nullptr)
	{
		return;
	}
	Scene* currentScene = SCENE_MGR.GetCurrentScene();
	sf::Vector2f mousePos = currentScene->ScreenToWorld(InputMgr::GetMousePosition());

	vibrationTimer += dt * vibrationSpeed;
	float xt = cosf(vibrationTimer) / (1 + sinf(vibrationTimer) * sinf(vibrationTimer));
	scopeVibration = { xt,sinf(vibrationTimer) * xt };

	scopeRecoilVel = Utils::Lerp(scopeRecoilVel, -scopeRecoil, dt * 5.f);
	scopeRecoil += scopeRecoilVel * dt;

	sf::Vector2f vibration = Utils::ElementProduct(scopeVibration, vibrationScale);

	scopePos = mousePos + vibration + scopeRecoil;
	circleView->SetPosition(scopePos);
}

void Player::UpdateBreathStatus(float dt)
{
	if (InputMgr::GetKeyPressing(sf::Keyboard::Space))
	{
		breath = Utils::Clamp(breath - dt, 0.f, maxBreath);
		vibrationSpeed = 0.5f;
	}
	else
	{
		breath = Utils::Clamp(breath + dt * 0.5f, 0.f, maxBreath);
	}
}
