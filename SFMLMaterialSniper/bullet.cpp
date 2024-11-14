#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	pos3d.x = position.x;
	pos3d.y = position.y;
	body.setPosition(position);
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bullet::Init()
{
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	fired = false;
}

void Bullet::Update(float dt)
{
	if (fired)
	{
		UpdateDragAccelation();
		vel3d += acc3d * dt;
		pos3d += vel3d * dt;
		SetPosition({ pos3d.x, pos3d.y });
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bullet::UpdateDragAccelation()
{
	// F = -C*rho*A*abs(V-W)*(V-W)/2
	float radius = 0.5f * diameter * 0.001f;
	sf::Vector3f force = -coeff * rho * Utils::PI * radius * radius * Utils::Magnitude(vel3d - wind) * (vel3d - wind) * 0.5f;
	acc3d = force / (weight * 0.001f); // a = F/m
	acc3d += gravity;
}

void Bullet::Fire(const sf::Vector3f& startpos, const sf::Vector3f& vel)
{
	fired = true;
	SetPosition(startpos);
	vel3d = vel;
}
