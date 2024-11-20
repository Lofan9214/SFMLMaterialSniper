#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texId, const std::string& name)
	: GameObject(name), textureId(texId)
{
}

void SpriteGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void SpriteGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void SpriteGo::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void SpriteGo::SetDisplacement(const sf::Vector2f& disp)
{
	displacement = disp;
	body.setPosition(position - displacement);
}

void SpriteGo::SetColor(const sf::Color& color)
{
	this->color = color;
	body.setColor(this->color);
}

void SpriteGo::Init()
{
}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(originPreset);
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void SpriteGo::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	body.setScale(scale);
}

void SpriteGo::Update(float dt)
{
}

void SpriteGo::Draw(sf::RenderTarget& renderTarget)
{
	body.setPosition(position + displacement);
	renderTarget.draw(body);
}

