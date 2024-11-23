#include "stdafx.h"
#include "ButtonRound.h"
#include "TextGo.h"

ButtonRound::ButtonRound(const std::string& name)
	: GameObject(name)
{
}

void ButtonRound::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	buttonBackground.setPosition(position);
	buttonText->SetPosition(position);
}

void ButtonRound::SetRotation(float angle)
{
	rotation = angle;
	buttonBackground.setRotation(rotation);
	buttonText->SetRotation(rotation);
}

void ButtonRound::SetScale(const sf::Vector2f& s)
{
	scale = s;
	buttonBackground.setScale(scale);
	//buttonText->SetScale(scale);
}

void ButtonRound::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(buttonBackground, originPreset);
		buttonText->SetOrigin(originPreset);
	}
}

void ButtonRound::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	buttonBackground.setOrigin(origin);
	buttonText->SetOrigin(origin);
}

void ButtonRound::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 450;

	buttonText = new TextGo(buttonFontId, "text");
	buttonText->Init();
	SetOrigin(Origins::MC);
}

void ButtonRound::Release()
{
	buttonText->Release();
	delete buttonText;
}

void ButtonRound::Reset()
{
	auto& texture = TEXTURE_MGR.Get(buttonTexId);
	sf::Vector2u texsize = texture.getSize();
	textureRect.x = texsize.x / 2;
	textureRect.y = texsize.y;
	buttonBackground.setTexture(texture);
	buttonBackground.setTextureRect({ {0,0} ,textureRect });
	SetOrigin(Origins::MC);

	buttonText->Reset();
}

void ButtonRound::Update(float dt)
{
	sf::Vector2f mousepos = SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition());
	sf::Image collisionImage = buttonBackground.getTexture()->copyToImage();
	sf::Vector2f point = buttonBackground.getInverseTransform().transformPoint(mousepos);
	sf::Cursor cursor;
	if (Utils::ExpandAndContains(buttonBackground.getGlobalBounds(), mousepos, 5))
	{
		if (point.x<0 || (int)point.x>= textureRect.x
			|| point.y < 0 || (int)point.y>= textureRect.y
			|| collisionImage.getPixel(point.x, point.y).a == 0)
		{
			if (buttonBackground.getTextureRect().left != 0)
			{
				buttonBackground.setTextureRect({ {0,0} ,textureRect });
			}
			if (cursor.loadFromSystem(sf::Cursor::Arrow))
			{
				FRAMEWORK.GetWindow().setMouseCursor(cursor);
			}
		}
		else
		{
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
	}

}

void ButtonRound::Draw(sf::RenderTarget& window)
{
	window.draw(buttonBackground);
	buttonText->Draw(window);
}

void ButtonRound::SetString(const std::string& text, bool usetable)
{
	buttonText->SetString(text, usetable);
}

void ButtonRound::SetCharSize(float size)
{
	buttonText->SetCharSize(size);
}

void ButtonRound::SetClicked(const std::function<void()>& event)
{
	Clicked = event;
}

