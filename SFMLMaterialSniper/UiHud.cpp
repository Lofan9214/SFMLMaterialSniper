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
	uiBar.setPosition(pos);
}

void UiHud::SetRotation(float angle)
{
	rotation = angle;
	uiBar.setRotation(rotation);
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	scale = s;
	uiBar.setScale(scale);
}

void UiHud::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(uiBar, originPreset);
	}
}

void UiHud::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	uiBar.setOrigin(origin);
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 300;

	uiBullets.resize(12);
}

void UiHud::Release()
{
	uiBullets.clear();
}

void UiHud::Reset()
{
	float textSize = 50.f;

	sf::Font& font = FONT_MGR.Get("fonts/malgun.ttf");

	textWind.SetFont(font);
	textWind.SetCharSize(textSize);
	textWind.SetFillColor(sf::Color::White);
	textWind.SetOrigin(Origins::BR);

	sf::Vector2f size = FRAMEWORK.GetDefaultSize();
	float bottomY = size.y - 25.f;

	textWind.SetPosition({ size.x - 25.f, bottomY });

	uiBar.setTexture(TEXTURE_MGR.Get(uiBarTexId));
	SetOrigin(Origins::BL);
	SetPosition({ 0.f,size.y });

	for (int i = 0; i < uiBullets.size();++i)
	{
		uiBullets[i].setTexture(TEXTURE_MGR.Get(uiBulletTexId));
		uiBullets[i].setScale({ 2.f,2.f });
		Utils::SetOrigin(uiBullets[i], Origins::BC);
		uiBullets[i].setPosition({ bulletStartPos.x + i * bulletOffset,size.y - bulletStartPos.y });
	}

	uiBreath.resize(4);
	uiBreath.setPrimitiveType(sf::PrimitiveType::Quads);
	uiBreath[0].position = { breathStartPos.x + breathMaxSize.x,size.y - breathStartPos.y + breathMaxSize.y };
	uiBreath[1].position = { breathStartPos.x + breathMaxSize.x,size.y - breathStartPos.y };
	uiBreath[2].position = { breathStartPos.x, size.y - breathStartPos.y };
	uiBreath[3].position = { breathStartPos.x, size.y - breathStartPos.y + breathMaxSize.y };
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
				float maxangle = 33.f;
				float peak = fireDuration * 0.5f;
				float angle = abs(maxangle / peak * (fireTimer - peak)) - maxangle;
				uiBullets[i].setRotation(angle);
			}
			else
			{
				uiBullets[i].setRotation(0.f);
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
	window.draw(uiBreath);
	window.draw(uiBar);

	for (int i = 0; i < ammo;++i)
	{
		window.draw(uiBullets[i]);
	}
}

void UiHud::SetWind(int wind)
{
	textWind.SetString("Wind : " + std::to_string(wind));
}

void UiHud::SetAmmo(int ammo)
{
	this->ammo = ammo;
}

void UiHud::SetBreath(float breath)
{
	uiBreath[0].position.x = breathStartPos.x + breathMaxSize.x * breath;
	uiBreath[1].position.x = breathStartPos.x + breathMaxSize.x * breath;

	uiBreath[0].color = { (sf::Uint8)(250 - 120 * breath),(sf::Uint8)(255 * (-breath * (2.f * breath - 2.8f))),(sf::Uint8)(255 * breath) };
	uiBreath[1].color = uiBreath[0].color;
	uiBreath[2].color = uiBreath[0].color - sf::Color(50, 50, 50, 0);
	uiBreath[3].color = uiBreath[2].color;
}

void UiHud::Fired()
{
	fireTimer = fireDuration;
}

void UiHud::OnLocalize(Languages lang)
{
	textWind.OnLocalize(lang);
}
