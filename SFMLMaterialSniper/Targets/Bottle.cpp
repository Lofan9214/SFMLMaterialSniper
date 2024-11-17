#include "stdafx.h"
#include "Bottle.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "GlassShard.h"

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

void Bottle::SetAnimationScale(const sf::Vector2f& scale)
{
	body.setScale(Utils::ElementProduct(this->scale, scale));
}

void Bottle::SetDisplacement(const sf::Vector2f& disp)
{
	displacement = disp;
	body.setOrigin(origin + displacement);
}

void Bottle::SetColor(const sf::Color& color)
{
	this->color = color;
	body.setColor(this->color);
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

	bullet = nullptr;

	animator.SetSprite(&body);
	animator.BindFunction(this);

}

void Bottle::Release()
{
}

void Bottle::Reset()
{
	active = true;

	animator.AddEvent("bottlespawn", 12, []() {SOUND_MGR.PlaySfx("sounds/targets/bottlespawn.mp3"); });

	animator.Play("animations/targets/bottlespawn.csv");
	animator.PlayQueue("animations/targets/bottleidle.csv");


	if (bullet==nullptr)
	{
		SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

		if (scene != nullptr)
		{
			bullet = dynamic_cast<Bullet*>(SCENE_MGR.GetCurrentScene()->FindGo("bullet"));
			TakeGlassShard = [scene]() {return scene->TakeGlassShard(); };
		}
	}

	SetOrigin(Origins::BC);
}

void Bottle::Update(float dt)
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

void Bottle::FixedUpdate(float dt)
{
	if (bullet == nullptr
		|| animator.GetCurrentClipId() != "bottleidle")
	{
		return;
	}

	sf::FloatRect bodyRect = GetGlobalBounds();
	if (bullet->GetPosition3().z > position3.z
		&& bullet->GetPosition3Previous().z < position3.z)
	{
		if (bodyRect.contains(bullet->GetPosition()))
		{
			std::cout << "hitbottle" << std::endl;
			bullet->Hit();
			active = false;
			for (int i = 0; i < 20; ++i)
			{
				SOUND_MGR.PlaySfx("sounds/targets/bottlehit.mp3");
				GlassShard* shard = TakeGlassShard();
				shard->Start({ position3.x + displacement.x,position3.y - body.getGlobalBounds().height * 0.5f + displacement.y ,position3.z });
			}
		}
	}
}

void Bottle::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}
