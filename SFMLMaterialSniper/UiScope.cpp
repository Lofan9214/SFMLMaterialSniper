#include "stdafx.h"
#include "UiScope.h"

UiScope::UiScope(const std::string& name)
	: GameObject(name)
{
}

void UiScope::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiScope::SetRotation(float angle)
{
	rotation = angle;
}

void UiScope::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiScope::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiScope::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiScope::Init()
{
}

void UiScope::Release()
{
}

void UiScope::Reset()
{
}

void UiScope::Update(float dt)
{
}

void UiScope::Draw(sf::RenderTarget& window)
{
}
