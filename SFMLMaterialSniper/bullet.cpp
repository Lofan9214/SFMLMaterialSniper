#include "stdafx.h"
#include "bullet.h"

bullet::bullet(const std::string& name)
	: GameObject(name)
{
}

void bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void bullet::Init()
{
}

void bullet::Release()
{
}

void bullet::Reset()
{
}

void bullet::Update(float dt)
{
	UpdateDragAccelation();
	vel3d += acc3d * dt;
	pos3d += vel3d * dt;


}

void bullet::Draw(sf::RenderWindow& window)
{
}

void bullet::UpdateDragAccelation()
{
	// F = -C*rho*A*abs(V-W)*(V-W)/2
	float radius = 0.5f * diameter * 0.001f;
	sf::Vector3f force = -coeff * rho * Utils::PI * radius * radius * Utils::Magnitude(vel3d - wind) * (vel3d - wind) * 0.5f;
	acc3d = force / (weight * 0.001f); // a = F/m
	acc3d += gravity;
}
