#include "stdafx.h"
#include "Bottle.h"
#include "Scene.h"
#include "Bullet.h"

Bottle::Bottle(const std::string& name)
	: GameObject(name)
{
}

void Bottle::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bottle::SetPosition(const sf::Vector3f& pos)
{
	position3 = pos;
	SetPosition({ position3.x ,position3.y });
	sf::Vector2f apparent = { 1.f,1.f };
	apparent *= defaultdistance / position3.z;
	sortingOrder = position3.z * -1.f;
	SetScale(apparent);
}

void Bottle::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bottle::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bottle::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bottle::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bottle::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 5;
}

void Bottle::Release()
{
}

void Bottle::Reset()
{
	bullet = dynamic_cast<Bullet*>(SCENE_MGR.GetCurrentScene()->FindGo("bullet"));
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::BC);
}

void Bottle::Update(float dt)
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

void Bottle::FixedUpdate(float dt)
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

void Bottle::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}
