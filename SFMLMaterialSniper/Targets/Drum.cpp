#include "stdafx.h"
#include "Drum.h"
#include "Scene.h"
#include "Bullet.h"

Drum::Drum(const std::string& name)
	: GameObject(name)
{
}

void Drum::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Drum::SetPosition(const sf::Vector3f& pos)
{
	position3 = pos;
	SetPosition({ position3.x ,position3.y });
	sf::Vector2f apparent = { 1.f,1.f };
	apparent *= defaultdistance / position3.z;
	sortingOrder = position3.z * -1.f;
	SetScale(apparent);
}

void Drum::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Drum::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Drum::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Drum::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Drum::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 5;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.AddEvent("drumhit", 63,
		[this]()
		{
			active = false;
		});
}

void Drum::Release()
{
}

void Drum::Reset()
{
	bullet = dynamic_cast<Bullet*>(SCENE_MGR.GetCurrentScene()->FindGo("bullet"));
	
	active = true;

	animator.Play("animations/targets/drumidle.csv");

	SetOrigin(Origins::BC);
}

void Drum::Update(float dt)
{
	animator.Update(dt);
	if (InputMgr::GetMouseButtonDown(sf::Mouse::XButton1))
	{
		SetPosition({ position3.x,position3.y,position3.z - 100.f });
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::XButton2))
	{
		SetPosition({ position3.x,position3.y,position3.z + 100.f });

	}
}

void Drum::FixedUpdate(float dt)
{
	if (bullet == nullptr)
	{
		return;
	}

	sf::FloatRect bodyRect = GetGlobalBounds();
	sf::Vector3f bulletpos = bullet->GetPosition3();
	sf::Vector3f bulletpospre = bullet->GetPosition3Previous();

	if (bulletpos.z > position3.z
		&& bulletpospre.z < position3.z)
	{
		float t = (position3.z - bulletpospre.z) / (bulletpos.z - bulletpospre.z);
		sf::Vector2f bulletlerppos = Utils::Lerp({ bulletpospre.x, bulletpospre.y }, { bulletpos.x, bulletpos.y }, t);

		if (bodyRect.contains(bulletlerppos))
		{
			std::cout << "hitdrum" << std::endl;
			animator.Play("animations/targets/drumhit.csv");
			bullet->Hit();
		}
	}

}

void Drum::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}
