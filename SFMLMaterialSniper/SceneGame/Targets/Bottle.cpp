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
	stand.setPosition(position);
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
	stand.setScale(scale);
}

void Bottle::SetAnimationScale(const sf::Vector2f& scale)
{
	body.setScale(Utils::ElementProduct(this->scale, scale));
	stand.setScale(Utils::ElementProduct(this->scale, scale));
}

void Bottle::SetDisplacement(const sf::Vector2f& disp)
{
	displacement = disp;
	body.setOrigin(origin - displacement);
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


	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.AddEvent("bottlespawn", 12, []() {SOUND_MGR.PlaySfx("sounds/targets/bottlespawn.mp3"); });

	stand.setFillColor(sf::Color::Black);
	stand.setSize({ 280.f,400.f });
	stand.setOrigin({ 140.f,80.f });
}

void Bottle::Release()
{
}

void Bottle::Reset()
{
	active = true;
	body.setColor(sf::Color::Transparent);

	animator.Play("animations/targets/bottlespawn.csv");
	animator.PlayQueue("animations/targets/bottleidle.csv");

	GetBulletList = nullptr;
	TakeGlassShard = nullptr;
	TargetHit = nullptr;

	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	if (scene != nullptr)
	{
		GetBulletList = [scene]() {return scene->GetBulletList();};
		TakeGlassShard = [scene]() {return scene->TakeGlassShard(); };
		TargetHit = [scene]() {scene->TargetHit();};
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
	if (!GetBulletList || animator.GetCurrentClipId() != "bottleidle")
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
				std::cout << "hitbottle" << std::endl;
				bullet->Hit();
				active = false;
				TargetHit();
				for (int i = 0; i < 20; ++i)
				{
					SOUND_MGR.PlaySfx("sounds/targets/bottlehit.mp3");
					GlassShard* shard = TakeGlassShard();
					shard->Start({ position3.x + displacement.x,position3.y - body.getGlobalBounds().height * 0.5f + displacement.y ,position3.z *-1.f });
				}
			}
			else if (stand.getGlobalBounds().contains(bulletlerppos))
			{
				bullet->SetRotation(Utils::RandomRange(0.f, 360.f));
				bullet->Hit(Bullet::Result::Ricochet);
			}
		}
	}
}

void Bottle::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(stand);
	renderTarget.draw(body);
}
