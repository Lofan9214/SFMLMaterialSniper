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
}

void Drum::Release()
{
}

void Drum::Reset()
{
	bullet = dynamic_cast<Bullet*>(SCENE_MGR.GetCurrentScene()->FindGo("bullet"));
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::BC);
}

void Drum::Update(float dt)
{
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
	if (bullet->GetPosition3().z > position3.z
		&& bullet->GetPosition3Previous().z < position3.z)
	{
		
		if (bodyRect.contains(bullet->GetPosition()))
		{
			std::cout << "hitdrum" << std::endl;
			bullet->Hit();
		}
	}

}

void Drum::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}
