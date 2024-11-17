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
}

void Player::SetRotation(float angle)
{
	rotation = angle;
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Player::Init()
{
	bullet = dynamic_cast<Bullet*>(SCENE_MGR.GetCurrentScene()->FindGo("bullet"));
	vibrationScale.x = 20.f;
	vibrationScale.y = 30.f;
}

void Player::Release()
{
}

void Player::Reset()
{
	ammo = clip;
	breath = maxBreath;
	vibrationTimer = 0.f;
}

void Player::Update(float dt)
{
	Scene* currentScene = SCENE_MGR.GetCurrentScene();

	UpdateScopeVibration(dt);

	sf::Vector2f vibrationDisplacement = Utils::ElementProduct(scopeVibration, vibrationScale);

	sf::Vector2f scopePos = vibrationDisplacement + currentScene->ScreenToWorld(InputMgr::GetMousePosition());

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (ammo > 0)
		{
			--ammo;
			SOUND_MGR.PlaySfx("sounds/bullet/bulletfire1.mp3");
			bullet->Reset();
			bullet->SetPosition({ scopePos.x, scopePos.y, 0.f });
			bullet->Fire(bullet->GetPosition3());
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

void Player::UpdateScopeVibration(float dt)
{
	vibrationTimer += dt * vibrationSpeed;

	float xt = cosf(vibrationTimer) / (1 + sinf(vibrationTimer) * sinf(vibrationTimer));

	scopeVibration = { xt,sinf(vibrationTimer) * xt };
}
