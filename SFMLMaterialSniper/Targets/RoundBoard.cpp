#include "stdafx.h"
#include "RoundBoard.h"
#include "Scene.h"
#include "Bullet.h"

RoundBoard::RoundBoard(const std::string& name)
	: GameObject(name)
{
}

void RoundBoard::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void RoundBoard::SetPosition(const sf::Vector3f& pos)
{
	position3 = pos;
	SetPosition({ position3.x ,position3.y });
	sf::Vector2f apparent = { 1.f,1.f };
	apparent *= defaultdistance / position3.z;
	SetScale(apparent);
}

void RoundBoard::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void RoundBoard::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void RoundBoard::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void RoundBoard::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void RoundBoard::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 5;
}

void RoundBoard::Release()
{
}

void RoundBoard::Reset()
{
	bullet = dynamic_cast<Bullet*>(SCENE_MGR.GetCurrentScene()->FindGo("bullet"));
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::BC);
}

void RoundBoard::Update(float dt)
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

void RoundBoard::FixedUpdate(float dt)
{
	if (bullet == nullptr)
	{
		return;
	}

	sf::FloatRect bodyRect = GetGlobalBounds();
	if (bullet->GetPosition3().z > position3.z
		&& bullet->GetPosition3Previous().z < position3.z)
	{
		sf::Image collisionImage = body.getTexture()->copyToImage();
		sf::Vector2f point = body.getInverseTransform().transformPoint(bullet->GetPosition());

		if (bodyRect.contains(bullet->GetPosition())
			&& collisionImage.getPixel(point.x, point.y).a != 0)
		{
			std::cout << "hitboard" << std::endl;
			bullet->Hit();
		}
	}

}

void RoundBoard::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}
