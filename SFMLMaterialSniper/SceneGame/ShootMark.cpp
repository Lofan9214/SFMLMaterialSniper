#include "stdafx.h"
#include "ShootMark.h"

ShootMark::ShootMark(const std::string& name)
	: GameObject(name)
{
}

void ShootMark::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	int arrowcnt = arrows.size();
	for (int i = 0; i < arrowcnt; ++i)
	{
		int vertexcnt = arrows[i].getVertexCount();
		for (int j = 0; j < vertexcnt; ++j)
		{
			arrows[i][j].position = { position.x + vertexPos[j].x,position.y + vertexPos[j].y + offsety * i };
		}
	}
}

void ShootMark::SetRotation(float angle)
{
	rotation = angle;
}

void ShootMark::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void ShootMark::SetAnimationScale(const sf::Vector2f& scale)
{
}

void ShootMark::SetDisplacement(const sf::Vector2f& disp)
{
}

void ShootMark::SetFlipX(bool flipX)
{
}

void ShootMark::SetOrigin(Origins preset)
{
	originPreset = preset;
}

void ShootMark::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
}

void ShootMark::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 3;

	for (int i = 1; i < 6; ++i)
	{
		colors.push_back(Utils::Lerp({ 0,0,0,0 }, { 255,200,70,255 }, i / 6.f));
	}
	colors.push_back({ 255,200,70,255 });
	for (int i = 5; i > 0; --i)
	{
		colors.push_back(Utils::Lerp({ 0,0,0,0 }, { 255,200,70,255 }, i / 6.f));
	}
	for (int i = 0; i < 10; ++i)
	{
		colors.push_back(sf::Color::Transparent);
	}

	vertexPos =
	{
		{-15.f,0.f},
		{-7.5f,0.f},
		{0.f,15.f},
		{0.f,7.5f},
		{15.f,0.f},
		{7.5f,0.f},
	};

	offsety = 10;

	for (int i = 0; i < 3; ++i)
	{
		sf::VertexArray va;
		va.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
		va.resize(6);

		for (int j = 0; j < 6; ++j)
		{
			va[j].color = colors[i];
			va[j].position = { vertexPos[j].x,vertexPos[j].y + offsety * i };
		}
		arrows.push_back(va);
	}
}

void ShootMark::Release()
{
}

void ShootMark::Reset()
{
	SetOrigin(Origins::MC);
	index = 10;
	duration = 1.f / 12.f;
	timer = 0.f;
	active = false;
}

void ShootMark::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		timer = 0.f;
		--index;
		int colorcnt = colors.size();
		if (index == 0)
		{
			index = colorcnt-1;
		}
		int arrowcnt = arrows.size();
		for (int i = 0; i < arrowcnt; ++i)
		{
			int vertexcnt = arrows[i].getVertexCount();
			for (int j = 0; j < vertexcnt; ++j)
			{
				arrows[i][j].color = colors[(index + i) % colorcnt];
			}
		}
	}
}

void ShootMark::Draw(sf::RenderTarget& window)
{
	for (auto& vertexarray : arrows)
	{
		window.draw(vertexarray);
	}
}

void ShootMark::OnHit()
{
	active = false;
}
