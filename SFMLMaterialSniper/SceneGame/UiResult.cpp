#include "stdafx.h"
#include "UiResult.h"

UiResult::UiResult(const std::string& name)
	: GameObject(name)
{
}

void UiResult::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiResult::SetRotation(float angle)
{
	rotation = angle;
}

void UiResult::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiResult::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiResult::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiResult::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 500;
}

void UiResult::Release()
{
}

void UiResult::Reset()
{
	active = false;
}

void UiResult::Update(float dt)
{
}

void UiResult::Draw(sf::RenderTarget& window)
{
}
