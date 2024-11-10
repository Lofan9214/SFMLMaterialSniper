#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& fontId, const std::string& name)
	:fontId(fontId),GameObject(name)
{
}

void TextGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(text, preset);
}

void TextGo::SetOrigin(const sf::Vector2f& neworigin)
{
	originPreset = Origins::Custom;
	origin = neworigin;
	text.setOrigin(neworigin);
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::SetTextString(const std::string& newtext)
{
	text.setString(newtext);
	SetOrigin(originPreset);
}

void TextGo::SetCharSize(unsigned int iSize)
{
	text.setCharacterSize(iSize);
}

void TextGo::SetFillColor(sf::Color color)
{
	text.setFillColor(color);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	text.setPosition(pos);
}

void TextGo::SetScale(const sf::Vector2f& scale)
{
}

void TextGo::Reset()
{
	auto& fontResMgr = ResourceMgr<sf::Font>::Instance();
	text.setFont(fontResMgr.Get(fontId));
	if (originPreset != Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::LateUpdate(float dt)
{
}

void TextGo::Update(float dt)
{
}

void TextGo::FixedUpdate(float dt)
{
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}

void TextGo::Draw(sf::RenderTexture& texture)
{
}

void TextGo::SetRotation(float angle)
{
}
