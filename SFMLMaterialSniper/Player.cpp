#include "stdafx.h"
#include "Player.h"

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
}

void Player::Release()
{
}

void Player::Reset()
{
}

void Player::Update(float dt)
{
}

void Player::Draw(sf::RenderTarget& window)
{
}

void Player::UpdateScopeVibration()
{
	float a = 50.f;
	float time = FRAMEWORK.GetTime()*vibration;

	sf::Vector2f LemniscatePos = { a * cosf(FRAMEWORK.GetTime()) / (1 + sinf(FRAMEWORK.GetTime()) * sinf(FRAMEWORK.GetTime())),a * sinf(FRAMEWORK.GetTime()) * cosf(FRAMEWORK.GetTime()) / (1 + sinf(FRAMEWORK.GetTime()) * sinf(FRAMEWORK.GetTime())) };
	//posminimap += LemniscatePos;
	//posminimap *= FRAMEWORK.GetDeltaTime() * 5.f;
}
