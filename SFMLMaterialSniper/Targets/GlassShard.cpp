#include "stdafx.h"
#include "GlassShard.h"

GlassShard::GlassShard(const std::string& name)
{
}

void GlassShard::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void GlassShard::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void GlassShard::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void GlassShard::SetType(int idx)
{
	index = idx;
	body.setTextureRect({ index * 63, 0, 63, 88 });
	SetOrigin(Origins::MC);
}

void GlassShard::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset < Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void GlassShard::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void GlassShard::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 5;
}

void GlassShard::Release()
{
}

void GlassShard::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::MC);
	frameTimer = 0.f;
	index = 0;
	active = false;
}

void GlassShard::Update(float dt)
{
	frameTimer += dt;
	if (frameTimer < frameDuration)
	{
		return;
	}
	frameTimer = 0.f;

	SetPosition(position + speed);
	speed.x *= 0.9f;
	speed.y += 0.8f;
}

void GlassShard::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}

void GlassShard::Start(const sf::Vector3f& startpos)
{
	active = true;
	
	SetPosition({ startpos.x, startpos.y });
	sortingOrder = startpos.z;

	index = Utils::RandomRange(0, 8);
	SetType(index);
	
	scale.x = Utils::RandomRange(0.2f, 0.4f);
	scale.y = Utils::RandomRange(0.2f, 0.4f);
	SetScale(scale);
	
	rotation = Utils::RandomRange(0.f, 360.f);
	SetRotation(rotation);
	
	speed.x = Utils::RandomRange(-6.f, 6.f);
	speed.y = Utils::RandomRange(-4.f, 0.8f);
}
