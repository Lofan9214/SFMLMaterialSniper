#include "stdafx.h"
#include "UiHud.h"
#include "TextGo.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiHud::SetRotation(float angle)
{
	rotation = angle;
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiHud::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiHud::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 300;

	uiBar = new SpriteGo(uiBarTexId, "uibar");
	uiBar->Init();

	uiBullets.resize(12);
	for (int i = 0; i < uiBullets.size();++i)
	{
		uiBullets[i] = new SpriteGo(uiBulletTexId, "uibullets");
		uiBullets[i]->Init();
	}
}

void UiHud::Release()
{
	for (int i = 0; i < uiBullets.size();++i)
	{
		delete uiBullets[i];
	}
	uiBullets.clear();

	delete uiBar;
}

void UiHud::Reset()
{
	float textSize = 50.f;

	sf::Font& font = FONT_MGR.Get("fonts/malgun.ttf");

	textAmmo.SetFont(font);
	textAmmo.SetCharSize(textSize);
	textAmmo.SetFillColor(sf::Color::White);
	textAmmo.SetOrigin(Origins::BL);

	textBreath.SetFont(font);
	textBreath.SetCharSize(textSize);
	textBreath.SetFillColor(sf::Color::White);
	textBreath.SetOrigin(Origins::BL);

	textWind.SetFont(font);
	textWind.SetCharSize(textSize);
	textWind.SetFillColor(sf::Color::White);
	textWind.SetOrigin(Origins::BR);

	sf::Vector2f size = FRAMEWORK.GetDefaultSize();
	float bottomY = size.y - 25.f;

	textAmmo.SetPosition({ 100.f, bottomY });
	textBreath.SetPosition({ size.x - 700.f, bottomY });
	textWind.SetPosition({ size.x - 25.f, bottomY });

	uiBar->Reset();
	uiBar->SetOrigin(Origins::BL);
	uiBar->SetPosition({ 0.f,size.y });

	for (int i = 0; i < uiBullets.size();++i)
	{
		uiBullets[i]->Reset();
		uiBullets[i]->SetScale({ 2.f,2.f });
		uiBullets[i]->SetOrigin(Origins::BC);
		uiBullets[i]->SetPosition({ 71.f + i * 31.f,size.y - 66.f });
	}
}

void UiHud::LateUpdate(float dt)
{
}

void UiHud::Update(float dt)
{
	float firelast = fireTimer;

	if (firelast > 0.f)
	{
		fireTimer -= dt;

		for (int i = 0; i < ammo;++i)
		{
			if (fireTimer > 0.f)
			{
				uiBullets[i]->SetRotation(sinf((fireDuration - fireTimer) * (Utils::PI / fireDuration)) * -25.f);
			}
			else
			{
				uiBullets[i]->SetRotation(0.f);
			}
		}
		if (firelast > fireDuration * 0.5f && fireTimer < fireDuration * 0.5f)
		{
			ammo--;
		}
	}
}

void UiHud::FixedUpdate(float dt)
{
}

void UiHud::Draw(sf::RenderTarget& window)
{
	textWind.Draw(window);
	textAmmo.Draw(window);
	textBreath.Draw(window);
	uiBar->Draw(window);

	for (int i = 0; i < ammo;++i)
	{
		uiBullets[i]->Draw(window);
	}
}

void UiHud::SetWind(int wind)
{
	textWind.SetString("Wind : " + std::to_string(wind));
}

void UiHud::SetAmmo(int ammo)
{
	this->ammo = ammo;
	textAmmo.SetString("Ammo : " + std::to_string(this->ammo));
}

void UiHud::SetBreath(float breath)
{
	textBreath.SetString("Breath : " + std::to_string(breath));
}

void UiHud::Fired()
{
	fireTimer = fireDuration;
}

void UiHud::OnLocalize(Languages lang)
{
	textAmmo.OnLocalize(lang);
	textBreath.OnLocalize(lang);
	textWind.OnLocalize(lang);
}
