#include "stdafx.h"
#include "UiStage.h"

UiStage::UiStage(const std::string& name)
	: GameObject(name)
{
}

void UiStage::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiStage::SetRotation(float angle)
{
	rotation = angle;
}

void UiStage::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiStage::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiStage::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiStage::Init()
{
}

void UiStage::Release()
{
}

void UiStage::Reset()
{
}

void UiStage::Update(float dt)
{
}

void UiStage::Draw(sf::RenderTarget& window)
{
}
