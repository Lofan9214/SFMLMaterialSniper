#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	position3.x = position.x;
	position3.y = position.y;
	body.setPosition(position);

	sf::Vector2f apparent;
	apparent.x = Utils::Clamp01(150.f / (position3.z + 300.f)) * (bFlipX ? -1.f : 1.f);
	apparent.y = Utils::Clamp01(150.f / (position3.z + 300.f)) * (bFlipY ? -1.f : 1.f);
	SetScale(apparent);
	SetOrigin(originPreset);
}

void Bullet::SetPosition(const sf::Vector3f& pos)
{
	position3 = pos;
	sortingOrder = position3.z * -1.f;
	SetPosition({ position3.x, position3.y });
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bullet::SetAnimationScale(const sf::Vector2f& scale)
{
	body.setScale(Utils::ElementProduct(this->scale, scale));
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.AddEvent("bullethit", 17,
		[this]()
		{
			if (returnBullet)
			{
				returnBullet(this);
			}
		});
	animator.AddEvent("bulletricochet", 3,
		[this]()
		{
			if (returnBullet)
			{
				returnBullet(this);
			}
		});
}

void Bullet::Release()
{
	animator.Pause();
}

void Bullet::Reset()
{
	SetOrigin(Origins::MC);
	active = false;
	status = Status::Ready;

	returnBullet = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		returnBullet = [scene](Bullet* bullet) { scene->ReturnBullet(bullet); };
	}

	const auto& data = BULLET_TABLE->Get(SAVEDATA_MGR.Get().selectedBullet);
	weight = data.weight;
	diameter = data.diameter;
	muzzleSpeed = data.muzzleSpeed;

	ANIMATIONCLIP_MGR.Load("animations/bullet/bulletflying.csv");
	ANIMATIONCLIP_MGR.Load("animations/bullet/bullethit.csv");
	ANIMATIONCLIP_MGR.Load("animations/bullet/bulletricochet.csv");
}

void Bullet::Update(float dt)
{
	animator.Update(dt);

	if (status == Status::Fired)
	{
		UpdateFired(dt);
	}
}

void Bullet::UpdateFired(float dt)
{
	if (animator.GetCurrentClipId() != "bulletflying")
	{
		return;
	}
	UpdateAccelation();
	velocity3d += acc3d * dt;
	position3Previous = position3;
	SetPosition(position3 + velocity3d * dt);
	if (position3.z > 1400.f && returnBullet)
	{
		returnBullet(this);
	}
}

void Bullet::UpdateHit(float dt)
{
}

void Bullet::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(body);
}

void Bullet::UpdateAccelation()
{
	// F = -C*rho*A*abs(V-W)*(V-W)/2
	//float radius = 0.5f * diameter * 0.001f;
	sf::Vector3f force = crossAreaConstant * Utils::Magnitude(velocity3d - wind * windMultiplier) * (velocity3d - wind * windMultiplier);
	acc3d = force / (weight * 0.001f); // a = F/m
	acc3d += gravity * gravityMultiplier;
}

void Bullet::Fire(const sf::Vector3f& startpos, const sf::Vector3f& dir)
{
	active = true;
	status = Status::Fired;

	SOUND_MGR.PlaySfx("sounds/bullet/bulletfire1.mp3");
	animator.Play("animations/bullet/bulletflying.csv");

	positionStarted = startpos;
	SetRotation(0.f);
	SetPosition(startpos);

	velocity3d = dir * muzzleSpeed;
}

void Bullet::Hit(Result result)
{
	SetPosition(position3Previous);
	if (result == Result::Hit1)
	{
		SetScale(scale * 1.5f);
		SOUND_MGR.PlaySfx("sounds/bullet/bullethit1.mp3");
		animator.Play("animations/bullet/bullethit.csv");
	}
	else if (result == Result::Ricochet)
	{
		SetScale(scale * 3.f);
		SOUND_MGR.PlaySfx("sounds/bullet/bulletricochet.mp3");
		animator.Play("animations/bullet/bulletricochet.csv");
	}
}

void Bullet::SetBulletType(const DataBullet& data)
{
	weight = data.weight;
	diameter = data.diameter;
	muzzleSpeed = data.muzzleSpeed;
	radius = 0.5f * diameter * 0.001f;
	crossAreaConstant =  -coeff * rho * Utils::PI * radius * radius* 0.5f;
}
