#include "stdafx.h"
#include "GlassShard.h"
#include "SceneGame.h"

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
	body.setTextureRect({ index * 252, 0, 252, 352 });
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
	sortingOrder = -1;
}

void GlassShard::Release()
{
}

void GlassShard::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::MC);
	index = 0;
	speed.x = 0.f;
	speed.y = 0.f;
	active = false;
	SetScale({ 0.25f,0.25f });
	returnThis = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		returnThis = [scene](GlassShard* glass) {scene->ReturnGlassShard(glass); };
		bounds = scene->WorldRegion();
	}
}

void GlassShard::Update(float dt)
{
	speed.x *= std::powf(0.75f, dt);
	speed.y += 450.f * dt;
	SetPosition(position + speed * dt);

	if (position.y > bounds.top + bounds.height + 300.f)
	{
		returnThis(this);
	}
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

	scale.x = Utils::RandomRange(0.05f, 0.1f);
	scale.y = Utils::RandomRange(0.05f, 0.1f);
	SetScale(scale);

	rotation = Utils::RandomRange(0.f, 360.f);
	SetRotation(rotation);

	speed.x = Utils::RandomRange(-100.f, 100.f);
	speed.y = Utils::RandomRange(-100.f, 20.f);
}
