#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& fontId, const std::string& name)
	:fontId(fontId), GameObject(name)
{
}

void TextGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset < Origins::Custom)
	{
		origin = Utils::SetOrigin(text, preset);
	}
}

void TextGo::SetOrigin(const sf::Vector2f& neworigin)
{
	originPreset = Origins::Custom;
	origin = neworigin;
	text.setOrigin(neworigin);
}

void TextGo::SetFont(const std::string& fontid)
{
	fontId = fontid;
	sf::Font& font = FONT_MGR.Get(fontId);
	SetFont(font);
}

void TextGo::SetFont(const sf::Font& font)
{
	text.setFont(font);
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::SetString(const std::string& newtext, bool loadFromTable)
{
	if (loadFromTable)
	{
		stringId = newtext;

		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		text.setString(STRING_TABLE->Get(stringId));
	}
	else
	{
		text.setString(newtext);
	}
	if (originPreset < Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::SetString(const std::string& id, const std::string& str)
{
	stringId = id;

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	text.setString(STRING_TABLE->Get(stringId) + converter.from_bytes(str));

	if (originPreset < Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::SetString(const std::wstring& str)
{
	text.setString(str);
	if (originPreset < Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::SetCharSize(unsigned int iSize)
{
	text.setCharacterSize(iSize);
	if (originPreset != Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::SetOutline(sf::Color color, float thickness)
{
	text.setOutlineColor(color);
	text.setOutlineThickness(thickness);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	text.setPosition(pos);
}

void TextGo::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	text.setScale(this->scale);
	if (originPreset != Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

sf::FloatRect TextGo::GetLocalBounds() const
{
	return text.getLocalBounds();
}

sf::FloatRect TextGo::GetGlobalBounds() const
{
	return text.getGlobalBounds();
}

void TextGo::SetColor(const sf::Color& color)
{
	text.setFillColor(color);
}

void TextGo::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	if (originPreset != Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::Update(float dt)
{
}

void TextGo::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(text);
}

void TextGo::SetRotation(float angle)
{
	rotation = angle;
	text.setRotation(rotation);
}
