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

void Gun::SetOffset(const sf::Vector2f& disp)
{
	offset = disp;
	body.setOrigin(origin - offset);
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
	sortingOrder = (int)GameDefine::SortingOrders::Gun;

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
				SetOrigin(Origins::ML);

				drawmuzzlefire = true;
				muzzlepos.x -= 50.f;
				muzzlefire.setColor({ 255,255,255,255 });
				muzzlefire.setPosition(muzzlepos);
				muzzlefire.setScale(0.625f, 0.875f);
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
				muzzlefire.setScale(0.875f, 0.1f);
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
			muzzlefire.setScale(0.925f, 0.1f);
			muzzlefire.setColor({ 255,255,255,54 });
			Utils::SetOrigin(muzzlefire, Origins::ML);
			drawmuzzlefire = false;
		});
	animator.AddEvent("gunfire", 17, [this]() {drawbody = false;});
}

void Gun::Release()
{
	animator.Pause();
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
	boltStatus = GameDefine::RecoilStatus::Ready;
	breathStatus = GameDefine::BreathStatus::Normal;
}

void Gun::Update(float dt)
{
	animator.Update(dt);
	UpdateScopeVibration(dt);
	UpdateScopeRecoil(dt);
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

	scopePos = mousePos + scopeVibration + scopeRecoil;
	circleView->SetPosition(scopePos);
}

void Gun::UpdateScopeRecoil(float dt)
{
	switch (boltStatus)
	{
	case GameDefine::RecoilStatus::Ready:
		break;
	case GameDefine::RecoilStatus::Fire:
	{
		recoilTimer += dt;
		scopeRecoil = scopeRecoilDir1 * (1.f - cosf(Utils::Clamp(recoilTimer * Utils::PI / firetobolt, 0.f, Utils::PI))) * firstRecoil;
		//scopeRecoilVel += scopeRecoilDir*sinf(recoilTimer*Utils::PI*2.f/firetobolt)*recoilSpeed*dt;
		break;
	}
	case GameDefine::RecoilStatus::BoltPulling:
		recoilTimer += dt;
		scopeRecoilDir1 = Utils::GetNormal(scopeRecoilDir1 + scopeRecoilDir2 * dt * 6.0f);
		if (recoilTimer < firetobolt * 0.75f)
		{
			scopeRecoil = scopeRecoilDir1 * (2.f + recoilTimer * 3.5f) * firstRecoil;
		}
		else
		{
			SetRecoilStatus(GameDefine::RecoilStatus::Recovery);
		}
		break;
	case GameDefine::RecoilStatus::Recovery:
		recoilTimer += dt;
		scopeRecoilDir1 = Utils::GetNormal(scopeRecoilDir1 + scopeRecoilDir2 * dt * 2.5f);
		scopeRecoil = scopeRecoilDir1 * secondRecoil * (cosf(recoilTimer * 1.5f * Utils::PI) + 1.f) * 0.5f;
		if (recoilTimer * 1.5f > 1.f)
			SetRecoilStatus(GameDefine::RecoilStatus::Ready);
		break;
	}
	//scopeRecoil += scopeRecoilVel * dt;
}

void Gun::UpdateScopeVibration(float dt)
{
	vibrationTimer += dt * vibrationSpeed;
	float xt = cosf(vibrationTimer) / (1 + sinf(vibrationTimer) * sinf(vibrationTimer));
	switch (breathStatus)
	{
	case GameDefine::BreathStatus::Normal:
	case GameDefine::BreathStatus::Hold:
		vibrationScale = Utils::Lerp(vibrationScale, vibrationScaleOrigin, dt * 2.5f);
		break;
	case GameDefine::BreathStatus::Over:
		vibrationScale = Utils::Lerp(vibrationScale, vibrationScaleOrigin * 2.f, dt * 5.f);
		break;
	}
	scopeVibration = Utils::ElementProduct({ xt,sinf(vibrationTimer) * xt }, vibrationScale);
}

void Gun::Draw(sf::RenderTarget& window)
{
	if (drawmuzzlefire)
	{
		window.draw(muzzlefire);
	}
	if (drawbody)
	{
		window.draw(body);
	}
}

void Gun::SetScope(int scopelevel)
{
	if (circleView != nullptr)
	{
		circleView->SetZoom(5.f);
		circleView->SetCircleRadius(150.f + scopelevel * 15.f);
	}
}

void Gun::SetRecoilScale(int control)
{
	firstRecoil = (1.f - control * 0.1f) * 70.f;
}

void Gun::SetRecoilStatus(GameDefine::RecoilStatus state)
{
	GameDefine::RecoilStatus prev = boltStatus;
	boltStatus = state;
	switch (boltStatus)
	{
	case GameDefine::RecoilStatus::Ready:
		//std::cout << recoilTimer << std::endl;
		//std::cout << scopeRecoil.x << std::endl;
		//std::cout << scopeRecoil.y << std::endl;
		scopeRecoil.x = 0.f;
		scopeRecoil.y = 0.f;
		break;
	case GameDefine::RecoilStatus::Fire:
	{
		recoilTimer = 0.f;
		float rand = Utils::RandomRange(Utils::PI * 1.30f, Utils::PI * 1.34f);
		scopeRecoilDir1.x = cosf(rand);
		scopeRecoilDir1.y = sinf(rand);
		break;
	}
	case GameDefine::RecoilStatus::BoltPulling:
	{
		//std::cout << recoilTimer << std::endl;

		recoilTimer = 0.f;
		float rand = Utils::RandomRange(Utils::PI * 1.75f, Utils::PI * 1.80f);
		scopeRecoilDir2.x = cosf(rand);
		scopeRecoilDir2.y = sinf(rand);
		break;
	}
	case GameDefine::RecoilStatus::Recovery:
		recoilTimer = 0.f;
		secondRecoil = Utils::Magnitude(scopeRecoil);
		break;
	}
}

void Gun::SetBreathStatus(GameDefine::BreathStatus state)
{
	GameDefine::BreathStatus prev = breathStatus;
	breathStatus = state;
	switch (breathStatus)
	{
	case GameDefine::BreathStatus::Normal:
		vibrationSpeed = 1.f;
		break;
	case GameDefine::BreathStatus::Hold:
		vibrationSpeed = 0.33f;
		break;
	case GameDefine::BreathStatus::Over:
		vibrationSpeed = 3.f;
		break;
	default:
		break;
	}
}

void Gun::Fire()
{
	sf::Vector3f firePos;
	firePos.x = scopePos.x;
	firePos.y = scopePos.y;
	firePos.z = 0;
	Bullet* bullet = TakeBullet();
	bullet->Fire(firePos);

	drawbody = true;
	SetRecoilStatus(GameDefine::RecoilStatus::Fire);

	body.setPosition(0.f, 0.f);
	SetOrigin(Origins::MC);
	sortingOrder = 200;
	animator.Play("animations/player/gunfire.csv");

	if (uiHud != nullptr)
	{
		uiHud->SetBoltStatus(UiHud::BoltStatus::Fired);
	}

	if (ScreenRecoil)
	{
		ScreenRecoil();
	}
}
