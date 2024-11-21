#include "stdafx.h"
#include "Drum.h"
#include "SceneGame.h"
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

void Drum::SetAnimationScale(const sf::Vector2f& scale)
{
	body.setScale(Utils::ElementProduct(this->scale, scale));
}

void Drum::SetDisplacement(const sf::Vector2f& disp)
{
	displacement = disp;
	body.setOrigin(origin - displacement);

}

void Drum::SetColor(const sf::Color& color)
{
	this->color = color;
	body.setColor(this->color);
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
	animator.AddEvent("drumspawn", 12, []() {SOUND_MGR.PlaySfx("sounds/targets/drumspawn.mp3"); });
	animator.AddEvent("drumhit", 55,
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
	GetBulletList = nullptr;
	TargetHit = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		GetBulletList = [scene]() {return scene->GetBulletList();};
		TargetHit = [scene]() {scene->TargetHit();};
	}

	active = true;
	body.setColor(sf::Color::Transparent);

	ANIMATIONCLIP_MGR.Load("animations/targets/drumidle.csv");
	animator.Play("animations/targets/drumspawn.csv");
	animator.PlayQueue("animations/targets/drumidle.csv");

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
	if (!GetBulletList || animator.GetCurrentClipId() != "drumidle")
	{
		return;
	}

	auto& bulletlist = GetBulletList();
	for (auto bullet : bulletlist)
	{
		sf::FloatRect bodyRect = GetGlobalBounds();
		sf::Vector3f bulletpos = bullet->GetPosition3();
		sf::Vector3f bulletpospre = bullet->GetPosition3Previous();

		if (bulletpos.z > position3.z
			&& bulletpospre.z < position3.z)
		{
			float t = (position3.z - bulletpospre.z) / (bulletpos.z - bulletpospre.z);
			sf::Vector2f bulletlerppos = Utils::Lerp({ bulletpospre.x, bulletpospre.y }, { bulletpos.x, bulletpos.y }, t);
			sf::Image collisionImage = body.getTexture()->copyToImage();
			sf::Vector2f point = body.getInverseTransform().transformPoint(bulletlerppos);
			if (bodyRect.contains(bulletlerppos)
				&& collisionImage.getPixel(point.x, point.y).a != 0)
			{
				SOUND_MGR.PlaySfx("sounds/targets/drumhit.mp3");
				std::cout << "hitdrum" << std::endl;
				animator.Play("animations/targets/drumhit.csv");
				if (bullet != nullptr)
				{
					bullet->Hit();
				}
				if (TargetHit)
				{
					TargetHit();
				}
			}
		}
	}
}

void Drum::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}
