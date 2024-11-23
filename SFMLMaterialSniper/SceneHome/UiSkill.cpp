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
	title->SetPosition(position + offsetTitle);
	manual->SetPosition(position + offsetManual);
	skillpoint->SetPosition(position + offsetSkillPoint);
	skillpoint2->SetPosition(position + offsetSkillPoint2);
	for (int i = 0; i < upArrows.size(); ++i)
	{
		upArrows[i].setPosition(position + offsetUpArrow + offsetSkillGroup * (float)i);
	}
	for (int i = 0; i < downArrows.size(); ++i)
	{
		downArrows[i].setPosition(position + offsetDownArrow + offsetSkillGroup * (float)i);
	}
	for (int i = 0; i < names.size(); ++i)
	{
		names[i]->SetPosition(position + offsetName + offsetSkillGroup * (float)i);
	}
	for (int i = 0; i < stars.size(); ++i)
	{
		for (int j = 0; j < stars[i].size(); ++j)
		{
			stars[i][j].setPosition(position + offsetStar + offsetStarbyStar * (float)j + offsetSkillGroup * (float)i);
		}
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
	texIdArrow = "graphics/ui/uiarrow.png";
	texIdStar = "graphics/ui/uistar.png";
	names.resize(5);
	for (int i = 0; i < names.size(); ++i)
	{
		names[i] = new TextGo(fontId, "name");
		names[i]->Init();
	}
	title = new TextGo(fontId, "title");
	title->Init();
	manual = new TextGo(fontId, "manual");
	manual->Init();
	skillpoint = new TextGo(fontId, "skillpoint");
	skillpoint->Init();
	skillpoint2 = new TextGo(fontId, "skillpoint2");
	skillpoint2->Init();

	textureRectArrow = { 40,20 };
	textureRectStar = { 84,83 };
	offsetTitle = { 250.f,15.f };
	offsetUpArrow = { 30.f,75.f };
	offsetDownArrow = { 70.f,120.f };
	offsetName = { 100.f,75.f };
	offsetManual = { 30.f,430.f };
	offsetSkillPoint = { 30.f,390.f };
	offsetSkillPoint2 = { 470.f,390.f };
	offsetStar = { 270.f ,72.f };
	offsetStarbyStar = { 40.f ,0.f };

	offsetSkillGroup = { 0.f,65.f };
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
	for (int i = 0; i < names.size(); ++i)
	{
		names[i]->Release();
		delete names[i];
	}

	title->Release();
	delete title;
	manual->Release();
	delete manual;
	skillpoint->Release();
	delete skillpoint;
	skillpoint2->Release();
	delete skillpoint2;
}

void UiSkill::Reset()
{
	manual->Reset();
	skillpoint->Reset();
	skillpoint2->Reset();

	title->Reset();
	title->SetString("SkillTitle", true);

	skillNames =
	{
		"SkillScopeSize",
		"SkillStablility",
		"SkillControl",
		"SkillReload",
		"SkillMagazine"
	};

	for (int i = 0; i < names.size(); ++i)
	{
		names[i]->Reset();
		names[i]->SetString(skillNames[i], true);
	}

	for (int i = 0; i < stars.size(); ++i)
	{
		for (int j = 0; j < stars[i].size(); ++j)
		{
			stars[i][j].setTexture(TEXTURE_MGR.Get(texIdStar));
			stars[i][j].setTextureRect({ {0,0} ,textureRectStar });
			stars[i][j].setScale({ 0.55f,0.55f });
		}
	}

	for (int i = 0; i < upArrows.size(); ++i)
	{
		upArrows[i].setTexture(TEXTURE_MGR.Get(texIdArrow));
		upArrows[i].setTextureRect({ {0,0} ,textureRectArrow });
	}

	for (int i = 0; i < downArrows.size(); ++i)
	{
		downArrows[i].setTexture(TEXTURE_MGR.Get(texIdArrow));
		downArrows[i].setTextureRect({ {0,0} ,textureRectArrow });
		downArrows[i].setRotation(180.f);
	}

	background.setSize({ 500.f,480.f });
	background.setFillColor({ 0,0,0,170 });

	title->SetOrigin(Origins::TC);
	title->SetString("SkillTitle", true);
	title->SetCharSize(40.f);

	skillpoint->SetString("SkillUp", " : " + std::to_string(0));
	skillpoint->SetCharSize(22.f);
	skillpoint2->SetOrigin(Origins::TR);
	skillpoint2->SetString("SkillPoint", " : " + std::to_string(SAVEDATA_MGR.Get().skillData.skillPoint));
	skillpoint2->SetCharSize(22.f);

	manual->SetCharSize(25.f);
	ReadSkillData();
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

	title->Draw(window);
	manual->Draw(window);
	skillpoint->Draw(window);
	skillpoint2->Draw(window);

	for (int i = 0; i < names.size(); ++i)
	{
		names[i]->Draw(window);
	}

	for (int i = 0; i < stars.size(); ++i)
	{
		for (int j = 0; j < stars[i].size(); ++j)
		{
			window.draw(stars[i][j]);
		}
	}
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
			if (point.x < 0 || (int)point.x >= textureRectArrow.x
				|| point.y < 0 || (int)point.y >= textureRectArrow.y
				|| collisionImage.getPixel(point.x, point.y).a == 0)
			{
				ChangeSkillManual(-1,false);
				if (upArrows[i].getTextureRect().left != 0)
				{
					upArrows[i].setTextureRect({ {0,0} ,textureRectArrow });
				}
				if (cursor.loadFromSystem(sf::Cursor::Arrow))
				{
					FRAMEWORK.GetWindow().setMouseCursor(cursor);
				}
			}
			else
			{
				ChangeSkillManual(i,true);
				if (cursor.loadFromSystem(sf::Cursor::Hand))
				{
					FRAMEWORK.GetWindow().setMouseCursor(cursor);
				}
				if (upArrows[i].getTextureRect().left == 0)
				{
					upArrows[i].setTextureRect({ {textureRectArrow.x,0} ,textureRectArrow });
				}
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
				{
					SkillUpDown(i, true);
				}
			}
		}
		else if (upArrows[i].getTextureRect().left != 0)
		{
			upArrows[i].setTextureRect({ {0,0} ,textureRectArrow });
		}
	}
	for (int i = 0; i < downArrows.size(); ++i)
	{
		collisionImage = downArrows[i].getTexture()->copyToImage();
		point = downArrows[i].getInverseTransform().transformPoint(mousepos);

		if (Utils::ExpandAndContains(downArrows[i].getGlobalBounds(), mousepos, 5))
		{
			if (point.x < 0 || (int)point.x >= textureRectArrow.x
				|| point.y < 0 || (int)point.y >= textureRectArrow.y
				|| collisionImage.getPixel(point.x, point.y).a == 0)
			{
				ChangeSkillManual(-1,false);
				if (downArrows[i].getTextureRect().left != 0)
				{
					downArrows[i].setTextureRect({ {0,0} ,textureRectArrow });
				}
				if (cursor.loadFromSystem(sf::Cursor::Arrow))
				{
					FRAMEWORK.GetWindow().setMouseCursor(cursor);
				}
			}
			else
			{
				ChangeSkillManual(i,false);
				if (cursor.loadFromSystem(sf::Cursor::Hand))
				{
					FRAMEWORK.GetWindow().setMouseCursor(cursor);
				}
				if (downArrows[i].getTextureRect().left == 0)
				{
					downArrows[i].setTextureRect({ {textureRectArrow.x * 2,0} ,textureRectArrow });
				}
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
				{
					SkillUpDown(i, false);
				}
			}
		}
		else if (downArrows[i].getTextureRect().left != 0)
		{
			downArrows[i].setTextureRect({ {0,0} ,textureRectArrow });
		}
	}
}

void UiSkill::ReadSkillData()
{
	auto& skilldata = SAVEDATA_MGR.Get().skillData;
	skillpoint2->SetString("SkillPoint", " : " + std::to_string(SAVEDATA_MGR.Get().skillData.skillPoint));

	for (int i = 0; i < 5; ++i)
	{
		if (i > 4 - skilldata.scopeSize)
		{
			stars[0][i].setTextureRect({ {textureRectStar.x,0},textureRectStar });
		}
		else
		{
			stars[0][i].setTextureRect({ {0,0},textureRectStar });
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		if (i > 4 - skilldata.stablility)
		{
			stars[1][i].setTextureRect({ {textureRectStar.x,0},textureRectStar });
		}
		else
		{
			stars[1][i].setTextureRect({ {0,0},textureRectStar });
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		if (i > 4 - skilldata.control)
		{
			stars[2][i].setTextureRect({ {textureRectStar.x,0},textureRectStar });
		}
		else
		{
			stars[2][i].setTextureRect({ {0,0},textureRectStar });
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		if (i > 4 - skilldata.reload)
		{
			stars[3][i].setTextureRect({ {textureRectStar.x,0},textureRectStar });
		}
		else
		{
			stars[3][i].setTextureRect({ {0,0},textureRectStar });
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		if (i > 4 - skilldata.magazine)
		{
			stars[4][i].setTextureRect({ {textureRectStar.x,0},textureRectStar });
		}
		else
		{
			stars[4][i].setTextureRect({ {0,0},textureRectStar });
		}
	}

}

void UiSkill::ChangeSkillManual(int index, bool up)
{
	if (index < 0)
	{
		manual->SetString("");
		skillpoint->SetString("SkillUp", " : " + std::to_string(0));
		return;
	}

	auto& skilldata = SAVEDATA_MGR.Get().skillData;
	manual->SetString(skillNames[index] + "Manual", true);

	int needpoint = 1;
	switch (index)
	{
	case 0:
		needpoint = 2 << skilldata.scopeSize;
		break;
	case 1:
		needpoint = 2 << skilldata.stablility;
		break;
	case 2:
		needpoint = 2 << skilldata.control;
		break;
	case 3:
		needpoint = 2 << skilldata.reload;
		break;
	case 4:
		needpoint = 2 << skilldata.magazine;
		break;
	}
	if (needpoint == 64 || needpoint == 1)
	{
		return;
	}
	if (!up)
	{
		needpoint = needpoint >> 1;
	}
	skillpoint->SetString("SkillUp", " : " + std::to_string(needpoint));
}

void UiSkill::SkillUpDown(int index, bool up)
{
	auto& skilldata = SAVEDATA_MGR.Get().skillData;
	int needpoint = 1;
	switch (index)
	{
	case 0:
		needpoint = 2 << skilldata.scopeSize;
		break;
	case 1:
		needpoint = 2 << skilldata.stablility;
		break;
	case 2:
		needpoint = 2 << skilldata.control;
		break;
	case 3:
		needpoint = 2 << skilldata.reload;
		break;
	case 4:
		needpoint = 2 << skilldata.magazine;
		break;
	}
	if (needpoint == 64 || needpoint == 1 || (up && needpoint > skilldata.skillPoint) || (!up && needpoint == 2))
	{
		return;
	}
	skilldata.skillPoint += up ? -needpoint : needpoint >> 1;
	switch (index)
	{
	case 0:
		up ? ++skilldata.scopeSize : --skilldata.scopeSize;
		break;
	case 1:
		up ? ++skilldata.stablility : --skilldata.stablility;
		break;
	case 2:
		up ? ++skilldata.control : --skilldata.control;
		break;
	case 3:
		up ? ++skilldata.reload : --skilldata.reload;
		break;
	case 4:
		up ? ++skilldata.magazine : --skilldata.magazine;
		break;
	}
	ReadSkillData();
}
