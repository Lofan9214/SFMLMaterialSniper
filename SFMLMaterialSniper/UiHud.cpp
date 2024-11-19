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

}

void UiHud::Release()
{
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
}

void UiHud::LateUpdate(float dt)
{
}

void UiHud::Update(float dt)
{
}

void UiHud::FixedUpdate(float dt)
{
}

void UiHud::Draw(sf::RenderTarget& window)
{
	textWind.Draw(window);
	textAmmo.Draw(window);
	textBreath.Draw(window);
}

void UiHud::SetWind(int wind)
{
	textWind.SetString("Wind : " + std::to_string(wind));
}

void UiHud::SetAmmo(int ammo)
{
	textAmmo.SetString("Ammo : " + std::to_string(ammo));
}

void UiHud::SetBreath(float breath)
{
	textBreath.SetString("Breath : " + std::to_string(breath));
}

void UiHud::OnLocalize(Languages lang)
{
	textAmmo.OnLocalize(lang);
	textBreath.OnLocalize(lang);
	textWind.OnLocalize(lang);
}
