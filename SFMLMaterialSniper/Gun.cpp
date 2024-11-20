#include "stdafx.h"
#include "Gun.h"
#include "CircleView.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Player.h"
#include "UiHud.h"

Gun::Gun(const std::string& name)
	: GameObject(name)
{
}

void Gun::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Gun::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Gun::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Gun::SetAnimationScale(const sf::Vector2f& scale)
{
	body.setScale(Utils::ElementProduct(this->scale, scale));
}

void Gun::SetDisplacement(const sf::Vector2f& disp)
{
	displacement = disp;
	body.setOrigin(origin - displacement);
}

void Gun::SetColor(const sf::Color& color)
{
	this->color = color;
	body.setColor(this->color);
}

void Gun::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Gun::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Gun::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 200;

	vibrationScale.x = vibrationScaleOrigin.x = 20.f;
	vibrationScale.y = vibrationScaleOrigin.y = 20.f;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.AddEvent("gunfire", 2, [this]()
		{
			if (player != nullptr)
			{
				sf::Vector2f muzzlepos = player->GetMuzzlePos();
				sortingOrder = 100;
				body.setPosition(muzzlepos);
				body.setScale(3.0f, 3.0f);
				SetOrigin(Origins::ML);

				drawmuzzlefire = true;
				muzzlepos.x -= 100.f;
				muzzlefire.setColor({ 255,255,255,255 });
				muzzlefire.setPosition(muzzlepos);
				muzzlefire.setScale(2.5f, 3.5f);
				Utils::SetOrigin(muzzlefire, Origins::ML);
			}
		});
	animator.AddEvent("gunfire", 3, [this]()
		{
			if (player != nullptr)
			{
				sf::Vector2f muzzlepos = player->GetMuzzlePos();
				muzzlepos.x += 110.f;
				muzzlefire.setPosition(muzzlepos);
				muzzlefire.setScale(3.5f, 0.4f);
				Utils::SetOrigin(muzzlefire, Origins::ML);
			}
			if (uiHud != nullptr)
			{
				uiHud->SetBoltStatus(UiHud::BoltStatus::BoltPulling);
			}
		});
	animator.AddEvent("gunfire", 4, [this]()
		{
			sf::Vector2f muzzlepos = player->GetMuzzlePos();
			muzzlepos.x -= 90.f;
			muzzlefire.setPosition(muzzlepos);
			muzzlefire.setScale(3.7f, 0.4f);
			muzzlefire.setColor({ 255,255,255,54 });
			Utils::SetOrigin(muzzlefire, Origins::ML);
			drawmuzzlefire = false;
		});
	animator.AddEvent("gunfire", 5, [this]() {if (ScreenRecoil) ScreenRecoil();});

	animator.AddEvent("gunfire", 17, [this]() {drawbody = false;});
}

void Gun::Release()
{
}

void Gun::Reset()
{
	ANIMATIONCLIP_MGR.Load("animations/player/gunfire.csv");

	muzzlefire.setTexture(TEXTURE_MGR.Get("graphics/player/muzzlefire.png"));

	vibrationTimer = 0.f;

	circleView = nullptr;
	player = nullptr;
	ScreenRecoil = nullptr;
	TakeBullet = nullptr;
	uiHud = nullptr;

	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		circleView = dynamic_cast<CircleView*>(scene->FindGo("circleView"));
		player = dynamic_cast<Player*>(scene->FindGo("player"));
		uiHud = dynamic_cast<UiHud*>(scene->FindGo("uiHud"));
		ScreenRecoil = [scene]() {scene->ResetScreenRecoilTimer();};
		TakeBullet = [scene]() {return scene->TakeBullet(); };
	}

	drawbody = false;
	drawmuzzlefire = false;
}

void Gun::Update(float dt)
{
	animator.Update(dt);
	UpdateScopeVibration(dt);
	UpdateScopePosition(dt);
}

void Gun::UpdateScopePosition(float dt)
{
	if (circleView == nullptr)
	{
		return;
	}
	Scene* currentScene = SCENE_MGR.GetCurrentScene();
	sf::Vector2f mousePos = currentScene->ScreenToWorld(InputMgr::GetMousePosition());

	vibrationTimer += dt * vibrationSpeed;
	float xt = cosf(vibrationTimer) / (1 + sinf(vibrationTimer) * sinf(vibrationTimer));
	scopeVibration = Utils::ElementProduct({ xt,sinf(vibrationTimer) * xt }, vibrationScale);

	scopeRecoilVel = Utils::Lerp(scopeRecoilVel, -scopeRecoil, dt * 4.f);
	scopeRecoil += scopeRecoilVel * dt;

	scopePos = mousePos + scopeVibration + scopeRecoil;
	circleView->SetPosition(scopePos);
}

void Gun::UpdateScopeVibration(float dt)
{
	if (breathover)
	{
		vibrationScale = Utils::Lerp(vibrationScale, vibrationScaleOrigin * 2.f, dt * 5.f);
	}
	if (vibrationScale.x != vibrationScaleOrigin.x)
	{
		vibrationScale = Utils::Lerp(vibrationScale, vibrationScaleOrigin, dt * 2.5f);
	}
}

void Gun::Draw(sf::RenderTarget& window)
{
	if (drawbody)
	{
		window.draw(body);
	}
	if (drawmuzzlefire)
	{
		window.draw(muzzlefire);
	}
}

void Gun::NextRoad()
{
	float rand = Utils::RandomRange(Utils::PI * 1.75f, Utils::PI * 1.85f);
	scopeRecoilVel.x += cosf(rand) * boltrecoilSpeed;
	scopeRecoilVel.y += sinf(rand) * boltrecoilSpeed;
}

void Gun::SetScope(int scopelevel)
{
	if (circleView != nullptr)
	{
		circleView->SetZoom(5.f);
		circleView->SetCircleRadius(150.f + scopelevel * 15.f);
	}
}

void Gun::SetRecoilSpeed(int control)
{
	recoilSpeed = (1.f - control * 0.1f) * 1400.f;
	boltrecoilSpeed = (1.f - control * 0.1f) * 700.f;
}

void Gun::Fire()
{
	sf::Vector3f firePos;
	firePos.x = scopePos.x;
	firePos.y = scopePos.y;
	firePos.z = 0;
	Bullet* bullet = TakeBullet();
	bullet->Fire(firePos);

	float rand = Utils::RandomRange(Utils::PI * 1.35f, Utils::PI * 1.40f);
	scopeRecoilVel.x = cosf(rand) * recoilSpeed;
	scopeRecoilVel.y = sinf(rand) * recoilSpeed;

	drawbody = true;

	body.setPosition(0.f, 0.f);
	SetOrigin(Origins::MC);
	sortingOrder = 200;
	animator.Play("animations/player/gunfire.csv");

	if (uiHud != nullptr)
	{
		uiHud->SetBoltStatus(UiHud::BoltStatus::Fired);
	}
}
