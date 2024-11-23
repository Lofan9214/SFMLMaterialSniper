#include "stdafx.h"
#include "BulletShell.h"
#include "SceneGame.h"

BulletShell::BulletShell(const std::string& name)
	: GameObject(name)
{
}

void BulletShell::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void BulletShell::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void BulletShell::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void BulletShell::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void BulletShell::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(newOrigin);
}

void BulletShell::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = (int)GameDefine::SortingOrders::BulletShell;

	SetOrigin(Origins::MC);

	screensize = FRAMEWORK.GetDefaultSize();

	gravity = 2500.f;
}

void BulletShell::Release()
{
}

void BulletShell::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetScale({ 0.375f,0.375f });
	SetOrigin(originPreset);

	ReturnBulletShell = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		ReturnBulletShell = [scene](BulletShell* shell) { scene->ReturnBulletShell(shell); };
	}
}

void BulletShell::Update(float dt)
{
	ejectionTimer -= dt * ejectionAngle;
	velocity.x *= powf(0.4f, dt);
	velocity.y += gravity * dt;
	SetPosition(position + velocity * dt);
	SetRotation(ejectionTimer);

	if (position.y > screensize.y*0.6f && ReturnBulletShell)
	{
		SOUND_MGR.PlaySfx("sounds/bullet/bulletshell.mp3");
		ReturnBulletShell(this);
	}
}

void BulletShell::Draw(sf::RenderTarget& window)
{
	window.draw(body);
}

void BulletShell::Eject(const sf::Vector2f& pos)
{
	SetPosition(pos);
	ejectionTimer = 0.f;
	velocity.x = Utils::RandomRange(-800.f, -900.f);
	velocity.y = Utils::RandomRange(-1200.f, -1300.f);
	SetRotation(ejectionTimer);
	ejectionAngle = Utils::RandomRange(170.f, 200.f);
}
