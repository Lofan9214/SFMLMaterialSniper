#include "stdafx.h"
#include "Player.h"
#include "Scene.h"
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
			scopeRecoilVel.x += cosf(rand) * (1600.f - skill.control * 160.f);
			scopeRecoilVel.y += sinf(rand) * (1600.f - skill.control * 160.f);
		});
}

void Player::Release()
{
}

void Player::Reset()
{
	ammo = clip;
	breath = maxBreath;
	vibrationTimer = 0.f;
	recoiltic = true;
	auto screensize = FRAMEWORK.GetWindowSizef();

	SetPosition({ screensize.x * -0.5f, screensize.y * 0.5f });
	SetOrigin(Origins::BL);
}

void Player::Update(float dt)
{
	animator.Update(dt);
	Scene* currentScene = SCENE_MGR.GetCurrentScene();

	sf::Vector2f mousePos = currentScene->ScreenToWorld(InputMgr::GetMousePosition());

	vibrationTimer += dt * vibrationSpeed;
	float xt = cosf(vibrationTimer) / (1 + sinf(vibrationTimer) * sinf(vibrationTimer));
	scopeVibration = { xt,sinf(vibrationTimer) * xt };

	scopeRecoilVel = Utils::Lerp(scopeRecoilVel, -scopeRecoil, dt * 7.0f);
	scopeRecoil += scopeRecoilVel * dt;

	sf::Vector2f vibration = Utils::ElementProduct(scopeVibration, vibrationScale);

	sf::Vector2f scopePos = mousePos + vibration + scopeRecoil;

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (ammo > 0)
		{
			--ammo;
			SOUND_MGR.PlaySfx("sounds/bullet/bulletfire1.mp3");
			bullet->Reset();
			bullet->SetPosition({ scopePos.x, scopePos.y, 0.f });
			bullet->Fire(bullet->GetPosition3());

			scopeRecoil.x = 0.f;
			scopeRecoil.y = 0.f;

			animator.Play("animations/player/playerfire.csv");
			animator.PlayQueue("animations/player/playeridle.csv");

			recoiltic = false;

			float rand = Utils::RandomRange(Utils::PI * 1.35f, Utils::PI * 1.40f);
			scopeRecoilVel.x = cosf(rand) * (3000.f - skill.control * 300.f);
			scopeRecoilVel.y = sinf(rand) * (3000.f - skill.control * 300.f);
		}
		else
		{
			//Todo 재장전 알림 만들어야 함
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Z)
		|| InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		ammo = clip;
	}

	if (InputMgr::GetKeyPressing(sf::Keyboard::Space))
	{
		breath -= dt;
		vibrationSpeed = 0.5f;
	}
	else
	{
		breath = Utils::Clamp(breath + dt * 0.5f, 0.f, maxBreath);
	}

	if (circleView != nullptr)
	{
		circleView->SetPosition(scopePos);
	}
}

void Player::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(body);
}