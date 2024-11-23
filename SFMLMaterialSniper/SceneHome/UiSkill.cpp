#include "stdafx.h"
#include "UiSkill.h"
#include "TextGo.h"

UiSkill::UiSkill(const std::string& name)
	: GameObject(name)
{
}

void UiSkill::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	background.setPosition(position);
	name->SetPosition(position + offsetName);
	weight->SetPosition(position + offsetWeight);
	diameter->SetPosition(position + offsetDiameter);
	muzzlespeed->SetPosition(position + offsetMuzzlespeed);
	for (int i = 0; i < upArrows.size(); ++i)
	{
		upArrows[i].setPosition(position + offsetUpArrow + offsetArrowGroup * (float)i);
	}
	for (int i = 0; i < downArrows.size(); ++i)
	{
		downArrows[i].setPosition(position + offsetDownArrow + offsetArrowGroup * (float)i);
	}
}

void UiSkill::SetRotation(float angle)
{
	rotation = angle;
}

void UiSkill::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiSkill::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiSkill::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiSkill::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 3;

	fontId = "fonts/malgun.ttf";
	texId = "graphics/ui/uiarrow.png";
	name = new TextGo(fontId, "name");
	weight = new TextGo(fontId, "weight");
	diameter = new TextGo(fontId, "diameter");
	muzzlespeed = new TextGo(fontId, "muzzlespeed");

	textureRect = { 40,20 };
	offsetUpArrow = { 30.f,15.f };
	offsetDownArrow = { 70.f,60.f };
	offsetName = { 30.f,70.f };
	offsetWeight = { 30.f,110.f };
	offsetDiameter = { 30.f,150.f };
	offsetMuzzlespeed = { 30.f,190.f };
	offsetArrowGroup = { 0.f,65.f };
	upArrows.resize(5);
	downArrows.resize(5);
	stars.resize(5);
	for (int i = 0; i < stars.size(); ++i)
	{
		stars[i].resize(5);
	}
}

void UiSkill::Release()
{
}

void UiSkill::Reset()
{
	name->Reset();
	weight->Reset();
	diameter->Reset();
	muzzlespeed->Reset();

	for (int i = 0; i < upArrows.size(); ++i)
	{
		upArrows[i].setTexture(TEXTURE_MGR.Get(texId));
		upArrows[i].setTextureRect({ {0,0} ,textureRect });
	}

	for (int i = 0; i < downArrows.size(); ++i)
	{
		downArrows[i].setTexture(TEXTURE_MGR.Get(texId));
		downArrows[i].setTextureRect({ {0,0} ,textureRect });
		downArrows[i].setRotation(180.f);
	}
	
	background.setSize({ 400.f,500.f });
	background.setFillColor({ 0,0,0,170 });
}

void UiSkill::Update(float dt)
{
	ButtonsUpdate();
}

void UiSkill::Draw(sf::RenderTarget& window)
{
	window.draw(background);
	for (int i = 0; i < upArrows.size(); ++i)
	{
		window.draw(upArrows[i]);
	}
	for (int i = 0; i < upArrows.size(); ++i)
	{
		window.draw(downArrows[i]);
	}

	name->Draw(window);
	weight->Draw(window);
	diameter->Draw(window);
	muzzlespeed->Draw(window);
}

void UiSkill::ButtonsUpdate()
{
	sf::Vector2f mousepos = SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition());
	sf::Image collisionImage;
	sf::Vector2f point;
	sf::Cursor cursor;

	for (int i = 0; i < upArrows.size(); ++i)
	{
		collisionImage = upArrows[i].getTexture()->copyToImage();
		point = upArrows[i].getInverseTransform().transformPoint(mousepos);

		if (Utils::ExpandAndContains(upArrows[i].getGlobalBounds(), mousepos, 5))
		{
			if (point.x < 0 || (int)point.x >= textureRect.x
				|| point.y < 0 || (int)point.y >= textureRect.y
				|| collisionImage.getPixel(point.x, point.y).a == 0)
			{
				if (upArrows[i].getTextureRect().left != 0)
				{
					upArrows[i].setTextureRect({ {0,0} ,textureRect });
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
				if (upArrows[i].getTextureRect().left == 0)
				{
					upArrows[i].setTextureRect({ {textureRect.x,0} ,textureRect });
				}
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
				{
					SkillUpDown(i, true);
				}
			}
		}
	}
	for (int i = 0; i < downArrows.size(); ++i)
	{
		collisionImage = downArrows[i].getTexture()->copyToImage();
		point = downArrows[i].getInverseTransform().transformPoint(mousepos);

		if (Utils::ExpandAndContains(downArrows[i].getGlobalBounds(), mousepos, 5))
		{
			if (point.x < 0 || (int)point.x >= textureRect.x
				|| point.y < 0 || (int)point.y >= textureRect.y
				|| collisionImage.getPixel(point.x, point.y).a == 0)
			{
				if (downArrows[i].getTextureRect().left != 0)
				{
					downArrows[i].setTextureRect({ {0,0} ,textureRect });
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
				if (downArrows[i].getTextureRect().left == 0)
				{
					downArrows[i].setTextureRect({ {textureRect.x * 2,0} ,textureRect });
				}
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
				{
					SkillUpDown(i, false);
				}
			}
		}
	}
}

void UiSkill::SkillUpDown(int index, bool up)
{
}
