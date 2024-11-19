#include "stdafx.h"
#include "Cartridge.h"

Cartridge::Cartridge(const std::string& name)
	: GameObject(name)
{
}

void Cartridge::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Cartridge::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Cartridge::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Cartridge::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Cartridge::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(newOrigin);
}

void Cartridge::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 190;

	SetOrigin(Origins::MC);

	gravity = 900.f;
}

void Cartridge::Release()
{
}

void Cartridge::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetScale({ 1.5f,1.5f });
	SetOrigin(originPreset);
}

void Cartridge::Update(float dt)
{
	ejectionTimer -= dt * ejectionAngle;
	velocity.x *= powf(0.65f, dt);
	velocity.y += gravity * dt;
	SetPosition(position + velocity * dt);
	SetRotation(ejectionTimer);
}

void Cartridge::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}

void Cartridge::Eject(const sf::Vector2f& pos)
{
	SetPosition(pos);
	ejectionTimer = 0.f;
	velocity.x = Utils::RandomRange(-500.f, -400.f);
	velocity.y = Utils::RandomRange(-550.f, -400.f);
	SetRotation(ejectionTimer);
	ejectionAngle = Utils::RandomRange(170.f, 200.f);
}
