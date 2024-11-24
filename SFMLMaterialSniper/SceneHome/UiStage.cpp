#include "stdafx.h"
#include "UiStage.h"
#include "TextGo.h"

UiStage::UiStage(const std::string& name)
	: GameObject(name)
{
}

void UiStage::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	background.setPosition(position);
	title->SetPosition(position + offsetTitle);
	manual->SetPosition(position + offsetManual);
	difficulty->SetPosition(position + offsetDifficulty);

	upArrow.setPosition(position + offsetUpArrow);
	downArrow.setPosition(position + offsetDownArrow);
}

void UiStage::SetRotation(float angle)
{
	rotation = angle;
}

void UiStage::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiStage::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiStage::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiStage::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 3;

	fontId = "fonts/malgun.ttf";
	texId = "graphics/ui/uiarrow.png";
	title = new TextGo(fontId, "title");
	manual = new TextGo(fontId, "manual");
	difficulty = new TextGo(fontId, "difficulty");
	textureRect = { 40,20 };
	offsetUpArrow = { 30.f,75.f };
	offsetDownArrow = { 70.f,120.f };
	offsetTitle = { 200.f,15.f };

	offsetManual = {30.f,135.f};
	offsetDifficulty = {85.f,75.f};
}

void UiStage::Release()
{
	title->Release();
	delete title;
	manual->Release();
	delete manual;
}

void UiStage::Reset()
{
	title->Reset();
	manual->Reset();
	difficulty->Reset();

	upArrow.setTexture(TEXTURE_MGR.Get(texId));
	upArrow.setTextureRect({ {0,0} ,textureRect });

	downArrow.setTexture(TEXTURE_MGR.Get(texId));
	downArrow.setTextureRect({ {0,0} ,textureRect });
	downArrow.setRotation(180.f);

	background.setSize({ 400,250 });
	background.setFillColor({ 0,0,0,170 });

	title->SetOrigin(Origins::TC);
	title->SetString("StageTitle", true);
	title->SetCharSize(40.f);
	//name->SetOrigin(Origins::TC);

	difficulty->SetString("StageDifficulty0", true);
	manual->SetString("StageManual", true);
	manual->SetCharSize(23.f);
}

void UiStage::Update(float dt)
{
	sf::Vector2f mousepos = SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition());
	sf::Image collisionImage = upArrow.getTexture()->copyToImage();
	sf::Vector2f point = upArrow.getInverseTransform().transformPoint(mousepos);
	sf::Cursor cursor;

	if (Utils::ExpandAndContains(upArrow.getGlobalBounds(), mousepos, 5))
	{
		if (point.x < 0 || (int)point.x >= textureRect.x
			|| point.y < 0 || (int)point.y >= textureRect.y
			|| collisionImage.getPixel(point.x, point.y).a == 0)
		{
			if (upArrow.getTextureRect().left != 0)
			{
				upArrow.setTextureRect({ {0,0} ,textureRect });
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
			if (upArrow.getTextureRect().left == 0)
			{
				upArrow.setTextureRect({ {textureRect.x,0} ,textureRect });
			}
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				if (Variables::difficulty<2)
				{
					++Variables::difficulty;
					SOUND_MGR.PlaySfx("sounds/ui/difficultychange.mp3");
					ShowDiff();
				}
			}
		}
	}
	else if (upArrow.getTextureRect().left != 0)
	{
		upArrow.setTextureRect({ {0,0} ,textureRect });
	}
	collisionImage = downArrow.getTexture()->copyToImage();
	point = downArrow.getInverseTransform().transformPoint(mousepos);

	if (Utils::ExpandAndContains(downArrow.getGlobalBounds(), mousepos, 5))
	{
		if (point.x < 0 || (int)point.x >= textureRect.x
			|| point.y < 0 || (int)point.y >= textureRect.y
			|| collisionImage.getPixel(point.x, point.y).a == 0)
		{
			sf::Cursor cursor;
			if (downArrow.getTextureRect().left != 0)
			{
				downArrow.setTextureRect({ {0,0} ,textureRect });
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
			if (downArrow.getTextureRect().left == 0)
			{
				downArrow.setTextureRect({ {textureRect.x * 2,0} ,textureRect });
			}
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				if (Variables::difficulty > 0)
				{
					--Variables::difficulty;
					ShowDiff();
					SOUND_MGR.PlaySfx("sounds/ui/difficultychange.mp3");
				}
			}
		}
	}
	else if (downArrow.getTextureRect().left != 0)
	{
		downArrow.setTextureRect({ {0,0} ,textureRect });
	}
}

void UiStage::Draw(sf::RenderTarget& window)
{
	window.draw(background);
	window.draw(upArrow);
	window.draw(downArrow);
	title->Draw(window);
	manual->Draw(window);
	difficulty->Draw(window);
}

void UiStage::ShowDiff()
{
	difficulty->SetString("StageDifficulty"+std::to_string(Variables::difficulty), true);
}
