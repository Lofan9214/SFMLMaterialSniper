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
}

void Player::Update(float dt)
{
	Scene* currentScene = SCENE_MGR.GetCurrentScene();

	UpdateScopeVibration(dt);

	sf::Vector2f vibrationDisplacement = { scopeVibration.x * vibrationScale.x, scopeVibration.y * vibrationScale.y };

	sf::Vector2f scopePos = vibrationDisplacement + currentScene->ScreenToWorld(InputMgr::GetMousePosition());

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		bullet->Reset();
		bullet->SetPosition({ scopePos.x, scopePos.y, 0.f });
		bullet->Fire(bullet->GetPosition3());
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
	float time = FRAMEWORK.GetTime() * vibrationSpeed;

	scopeVibration = { cosf(time) / (1 + sinf(time) * sinf(time)),sinf(time) * cosf(time) / (1 + sinf(time) * sinf(time)) };
}
