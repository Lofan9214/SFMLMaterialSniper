#include "stdafx.h"
#include "UiBullet.h"

UiBullet::UiBullet(const std::string& name)
	: GameObject(name)
{
}

void UiBullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiBullet::SetRotation(float angle)
{
	rotation = angle;
}

void UiBullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiBullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiBullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiBullet::Init()
{
}

void UiBullet::Release()
{
}

void UiBullet::Reset()
{
}

void UiBullet::Update(float dt)
{
}

void UiBullet::Draw(sf::RenderTarget& window)
{
}
