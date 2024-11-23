#include "stdafx.h"
#include "UiWindCone.h"

WindCone::WindCone(const std::string& name)
	: GameObject(name)
{
}

void WindCone::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void WindCone::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void WindCone::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void WindCone::SetAnimationScale(const sf::Vector2f& scale)
{
}

void WindCone::SetDisplacement(const sf::Vector2f& disp)
{
}

void WindCone::SetFlipX(bool flipX)
{
	bFlipX = flipX;
	if (bFlipX && scale.x > 0.f
		|| !bFlipX && scale.x < 0.f)
	{
		SetScale({ scale.x * -1.f,scale.y });
	}
}

void WindCone::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void WindCone::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void WindCone::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.Play("animations/ui/windconeidle.csv");
}

void WindCone::Release()
{
	animator.Stop();
}

void WindCone::Reset()
{
	SetOrigin(Origins::MC);
}

void WindCone::Update(float dt)
{
	animator.Update(dt);
}

void WindCone::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}

void WindCone::SetWindSpeed(int speed)
{
	if (speed != 0)
	{
		if (animator.GetCurrentClipId() != "windconeblow")
		{
			animator.Play("animations/ui/windconeblow.csv");
		}
		SetFlipX(speed < 0);
		animator.SetFPS(speed * 4);
	}
	else if (animator.GetCurrentClipId() != "windconeidle")
	{
		animator.Play("animations/ui/windconeidle.csv");
	}
}
