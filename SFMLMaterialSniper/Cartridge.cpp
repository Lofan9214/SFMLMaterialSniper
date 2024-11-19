#include "stdafx.h"
#include "Cartridge.h"

Cartridge::Cartridge(const std::string& name)
	: GameObject(name)
{
}

void Cartridge::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Cartridge::SetRotation(float angle)
{
	rotation = angle;
}

void Cartridge::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Cartridge::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Cartridge::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Cartridge::Init()
{
}

void Cartridge::Release()
{
}

void Cartridge::Reset()
{
}

void Cartridge::Update(float dt)
{
}

void Cartridge::Draw(sf::RenderTarget& window)
{
}
