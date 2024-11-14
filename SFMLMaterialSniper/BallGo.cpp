#include "stdafx.h"
#include "BallGo.h"
#include "BatGo.h"

BallGo::BallGo(const std::string& name)
	:GameObject(name)
{
}

void BallGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(position);
}

void BallGo::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	body.setScale(this->scale);
}

void BallGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset < Origins::Custom)
	{
		origin = Utils::SetOrigin(body, preset);
	}
}

void BallGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void BallGo::Init()
{
	float diameter = 20.f;
	float radius = diameter * 0.5f;

	body.setRadius(radius);
	body.setFillColor(sf::Color::White);
	SetOrigin(Origins::BC);

	direction = { 0.f,0.f };
	speed = 0.f;

	movableBounds = FRAMEWORK.GetWindowBounds();
	movableBounds.top += diameter;
	movableBounds.height -= diameter;
	movableBounds.left += radius;
	movableBounds.width -= diameter;
}

void BallGo::Reset()
{
	ResetHitBottom();
	ResetHitBat();
	direction = { 0.f,0.f };
	speed = 0.f;
}

void BallGo::Release()
{
}

void BallGo::LateUpdate(float dt)
{
}

void BallGo::Update(float dt)
{
	sf::Vector2f newPos = position + direction * speed * dt;
	sf::FloatRect bodyRect = body.getGlobalBounds();
	sf::FloatRect batRect = bat->GetGlobalBounds();


	if (newPos.y < movableBounds.top)
	{
		direction.y *= -1.f;
		newPos.y = movableBounds.top;
		//newPos.y = movableBounds.top + movableBounds.top - newPos.y;
	}
	else if (newPos.y > movableBounds.top + movableBounds.height)
	{
		hitBottom = true;
		direction.y *= -1.f;
		newPos.y = movableBounds.top + movableBounds.height;
		//newPos.y = movableBounds.top + movableBounds.height + movableBounds.height - newPos.y;
	}

	if (newPos.x < movableBounds.left)
	{
		direction.x *= -1.f;
		newPos.x = movableBounds.left;
		//newPos.x = movableBounds.left+ movableBounds.left - newPos.x;
	}
	else if (newPos.x > movableBounds.left + movableBounds.width)
	{
		direction.x *= -1.f;
		newPos.x = movableBounds.left + movableBounds.width;
		//newPos.x = movableBounds.left + movableBounds.width + movableBounds.width - newPos.x;
	}

	if (bodyRect.intersects(batRect)
		&& bodyRect.top + bodyRect.height < batRect.top + batRect.height)
	{
		hitBat = true;
		//direction.y *= -1.f;
		direction = Utils::RandomOnUnitCircle();
		if (direction.y > 0.f)
		{
			direction.y *= -1.f;
		}
		newPos.y = bat->GetPosition().y;

		//newPos.y = bat->GetPosition().y + bat->GetPosition().y - GetPosition().y;
	}

	SetPosition(newPos);
}

void BallGo::FixedUpdate(float dt)
{
}

void BallGo::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(body);
}

bool BallGo::GetHitBottom() const
{
	return hitBottom;
}

void BallGo::ResetHitBottom()
{
	hitBottom = false;
}

bool BallGo::GetHitBat() const
{
	return hitBat;
}

void BallGo::ResetHitBat()
{
	hitBat = false;
}
