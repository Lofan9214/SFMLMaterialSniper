#include "stdafx.h"
#include "UiWindIcon.h"

WindIcon::WindIcon(const std::string& name)
	: GameObject(name)
{
}

void WindIcon::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void WindIcon::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void WindIcon::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void WindIcon::SetAnimationScale(const sf::Vector2f& scale)
{
}

void WindIcon::SetOffset(const sf::Vector2f& disp)
{
}

void WindIcon::SetFlipX(bool flipX)
{
	bFlipX = flipX;
	//if ((bFlipX && scale.x > 0.f)
	//	|| (!bFlipX && scale.x < 0.f))
	//{
	//	SetScale({ scale.x * -1.f,scale.y });
	//}
}

void WindIcon::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void WindIcon::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void WindIcon::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	SetType(Type::Cone);
}

void WindIcon::Release()
{
	animator.Pause();
}

void WindIcon::Reset()
{
	SetWindSpeed(0);
}

void WindIcon::Update(float dt)
{
	animator.Update(dt);
}

void WindIcon::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}

void WindIcon::SetType(Type type)
{
	this->type = type;
	if (this->type == Type::Cone)
	{
		animator.Play("animations/ui/windconeidle.csv");
	}
	else if (this->type == Type::Arrow)
	{
		animator.Play("animations/ui/windarrow.csv");
	}
}

void WindIcon::SetWindSpeed(int speed)
{
	if (this->speed == speed)
	{
		return;
	}
	this->speed = speed;
	if (speed != 0)
	{
		//if (type == Type::Cone
		//	&& animator.GetCurrentClipId() != "windconeblow")
		//{
		//	animator.Play("animations/ui/windconeblow.csv");
		//
		//	if ((speed < 0 && scale.x > 0.f)
		//		|| (speed > 0 && scale.x < 0.f))
		//	{
		//		SetScale({ scale.x * -1.f,scale.y });
		//	}
		//}
		if (type == Type::Arrow)
		{
			active = true;

			if ((speed > 0 && scale.x > 0.f)
				|| (speed < 0 && scale.x < 0.f))
			{
				SetScale({ scale.x * -1.f,scale.y });
			}
			animator.SetFPS(speed * 4);
		}
	}
	else
	{
		if (type == Type::Arrow)
		{
			active = false;
		}
		if (type == Type::Cone && animator.GetCurrentClipId() != "windconeidle")
		{
			animator.Play("animations/ui/windconeidle.csv");
		}
	}
}
