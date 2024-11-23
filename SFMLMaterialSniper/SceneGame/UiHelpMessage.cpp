#include "stdafx.h"
#include "UiHelpMessage.h"

HelpMessage::HelpMessage(const std::string& name)
	: GameObject(name)
{
}

void HelpMessage::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void HelpMessage::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void HelpMessage::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void HelpMessage::SetAnimationScale(const sf::Vector2f& scale)
{
}

void HelpMessage::SetOffset(const sf::Vector2f& disp)
{
}

void HelpMessage::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void HelpMessage::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void HelpMessage::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.Play("animations/ui/" + name + ".csv");
}

void HelpMessage::Release()
{
}

void HelpMessage::Reset()
{
	animator.Play("animations/ui/" + name + ".csv");
	SetOrigin(Origins::MC);

	duration = 0.f;
	timer = 0.f;
}

void HelpMessage::Update(float dt)
{
	animator.Update(dt);
	if (duration != 0.f)
	{
		timer += dt;
		if (timer > duration)
		{
			active = false;
		}
	}
}

void HelpMessage::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}

void HelpMessage::StartTimer(float duration)
{
	this->duration = duration;
	timer = 0.f;
}
