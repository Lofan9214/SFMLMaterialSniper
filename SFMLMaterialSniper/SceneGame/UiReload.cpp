#include "stdafx.h"
#include "UiReload.h"

Reload::Reload(const std::string& name)
	: GameObject(name)
{
}

void Reload::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Reload::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Reload::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Reload::SetAnimationScale(const sf::Vector2f& scale)
{
}

void Reload::SetDisplacement(const sf::Vector2f& disp)
{
}

void Reload::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body,originPreset);
	}
}

void Reload::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Reload::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.Play("animations/ui/reload.csv");
}

void Reload::Release()
{
}

void Reload::Reset()
{
	SetOrigin(Origins::MC);
}

void Reload::Update(float dt)
{
	animator.Update(dt);
}

void Reload::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}
