#include "stdafx.h"
#include "ButtonRound.h"

ButtonRound::ButtonRound(const std::string& name)
	: GameObject(name)
{
}

void ButtonRound::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	buttonBackground.setPosition(position);
	buttonText.setPosition(position);
}

void ButtonRound::SetRotation(float angle)
{
	rotation = angle;
	buttonBackground.setRotation(rotation);
	buttonText.setRotation(rotation);
}

void ButtonRound::SetScale(const sf::Vector2f& s)
{
	scale = s;
	buttonBackground.setScale(scale);
	buttonText.setScale(scale);
}

void ButtonRound::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(buttonBackground, originPreset);
		Utils::SetOrigin(buttonText, originPreset);
	}
}

void ButtonRound::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	buttonBackground.setOrigin(origin);
	buttonText.setOrigin(origin);
}

void ButtonRound::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 450;

	SetOrigin(Origins::MC);
}

void ButtonRound::Release()
{
}

void ButtonRound::Reset()
{
	auto& texture = TEXTURE_MGR.Get(buttonTexId);
	sf::Vector2u texsize = texture.getSize();
	textureRect.x = texsize.x / 2;
	textureRect.y = texsize.y;
	buttonBackground.setTexture(texture);
	buttonBackground.setTextureRect({ {0,0} ,textureRect });

	buttonText.setFont(FONT_MGR.Get(buttonFontId));
}

void ButtonRound::Update(float dt)
{
	sf::Vector2f mousepos = SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition());
	sf::Image collisionImage = buttonBackground.getTexture()->copyToImage();
	sf::Vector2f point = buttonBackground.getInverseTransform().transformPoint(mousepos);
	if (buttonBackground.getGlobalBounds().contains(mousepos) && collisionImage.getPixel(point.x, point.y).a != 0)
	{
		sf::Cursor cursor;
		if (cursor.loadFromSystem(sf::Cursor::Hand))
		{
			FRAMEWORK.GetWindow().setMouseCursor(cursor);
		}
		if (buttonBackground.getTextureRect().left == 0)
		{
			buttonBackground.setTextureRect({ {textureRect.x,0} ,textureRect });
		}
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && Clicked)
		{
			Clicked();
		}
	}
	else
	{
		sf::Cursor cursor;
		if (buttonBackground.getTextureRect().left != 0)
		{
			buttonBackground.setTextureRect({ {0,0} ,textureRect });
		}
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
		{
			FRAMEWORK.GetWindow().setMouseCursor(cursor);
		}
	}
}

void ButtonRound::Draw(sf::RenderTarget& window)
{
	window.draw(buttonBackground);
	window.draw(buttonText);
}

void ButtonRound::SetString(const std::string& text)
{
	buttonText.setString(text);
	SetOrigin(originPreset);
}
void ButtonRound::SetString(const std::wstring& text)
{
	buttonText.setString(text);
	SetOrigin(originPreset);
}

void ButtonRound::SetClicked(const std::function<void()>& event)
{
	Clicked = event;
}

