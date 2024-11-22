#include "stdafx.h"
#include "UiSkill.h"

UiSkill::UiSkill(const std::string& name)
	: GameObject(name)
{
}

void UiSkill::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiSkill::SetRotation(float angle)
{
	rotation = angle;
}

void UiSkill::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiSkill::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiSkill::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiSkill::Init()
{
}

void UiSkill::Release()
{
}

void UiSkill::Reset()
{
}

void UiSkill::Update(float dt)
{
}

void UiSkill::Draw(sf::RenderTarget& window)
{
}
