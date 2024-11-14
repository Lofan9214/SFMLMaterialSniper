#include "stdafx.h"
#include "Icon.h"

Icon::Icon(const std::string& name)
	: GameObject(name)
{
}

void Icon::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	drawnicon.setPosition(position);

}

void Icon::SetRotation(float angle)
{
	rotation = angle;
}

void Icon::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Icon::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(drawnicon, originPreset);
	}
}

void Icon::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	drawnicon.setOrigin(origin);
}

void Icon::Init()
{
}

void Icon::Release()
{
}

void Icon::Reset()
{

	auto& tex = TEXTURE_MGR.Get(textureId);
	icon.setTexture(tex);
	mask.setPrimitiveType(sf::PrimitiveType::TriangleFan);
	mask.resize(5);
	sf::Vector2f iconsize = icon.getLocalBounds().getSize();
	float radius = (iconsize.x + iconsize.y) * 2.f;
	mask[0].position = iconsize * 0.5f;
	mask[0].color = sf::Color({ 90,90,90,0 });
	int vac = mask.getVertexCount();
	for (int i = 1; i < vac; ++i)
	{
		float angle = ((4 - i) / 3.f * 2.f - 0.5f) * Utils::PI;
		mask[i].position = { radius * cosf(angle),radius * sinf(angle) };
		mask[i].position += iconsize * 0.5f;
		mask[i].color = sf::Color({ 90,90,90,0 });
	}
	texture.create(tex.getSize().x, tex.getSize().y);
	timer = 0.f;
	maxTime = 5.f;
}

void Icon::Update(float dt)
{
	sf::Vector2f iconsize = icon.getLocalBounds().getSize();
	float radius = (iconsize.x + iconsize.y) * 2.f;
	int vac = mask.getVertexCount();
	float ratio = Utils::Clamp01(timer / maxTime);

	for (int i =  1; i < vac; ++i)
	{
		float angle = ((4 - i) / 3.f * 2.f * (1 - ratio) - 0.5f) * Utils::PI;
		mask[i].position = { radius * cosf(angle),radius * sinf(angle) };
		mask[i].position += iconsize * 0.5f;
	}
	texture.clear(sf::Color(0,0,0,0));
	
	texture.draw(icon);
	if (ratio < 1.f)
	{
		maskRenderState.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::One, sf::BlendMode::ReverseSubtract);
		texture.draw(mask, maskRenderState);
	}
	texture.display();
	drawnicon.setTexture(texture.getTexture(), true);
	drawnicon.setScale({ 2.f ,2.f });
	SetOrigin(originPreset);
}

void Icon::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(drawnicon);
}

void Icon::SetTime(float time, float delay)
{
	timer = time;
	maxTime = delay;
}
