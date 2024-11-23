#include "stdafx.h"
#include "UiBullet.h"
#include "TextGo.h"

UiBullet::UiBullet(const std::string& name)
	: GameObject(name)
{
}

void UiBullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	background.setPosition(position);
	name->SetPosition(position + offsetName);
	weight->SetPosition(position + offsetWeight);
	diameter->SetPosition(position + offsetDiameter);
	muzzlespeed->SetPosition(position + offsetMuzzlespeed);
	upArrow.setPosition(position + offsetUpArrow);
	downArrow.setPosition(position + offsetDownArrow);
}

void UiBullet::SetRotation(float angle)
{
	rotation = angle;
	background.setRotation(rotation);
}

void UiBullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	background.setScale(scale);
}

void UiBullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiBullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
}

void UiBullet::Init()
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
}

void UiBullet::Release()
{
	name->Release();
	delete name;
	weight->Release();
	delete weight;
	diameter->Release();
	delete diameter;
	muzzlespeed->Release();
	delete muzzlespeed;
}

void UiBullet::Reset()
{
	name->Reset();
	weight->Reset();
	diameter->Reset();
	muzzlespeed->Reset();

	upArrow.setTexture(TEXTURE_MGR.Get(texId));
	upArrow.setTextureRect({ {0,0} ,textureRect });

	downArrow.setTexture(TEXTURE_MGR.Get(texId));
	downArrow.setTextureRect({ {0,0} ,textureRect });
	downArrow.setRotation(180.f);

	ReadDataBullet();

	background.setSize({ 400,250 });
	background.setFillColor({ 0,0,0,170 });
}

void UiBullet::Update(float dt)
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
				BULLET_TABLE->Change(true);
				ReadDataBullet();
			}
		}
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
				BULLET_TABLE->Change(false);
				ReadDataBullet();
			}
		}
	}
}

void UiBullet::Draw(sf::RenderTarget& window)
{
	window.draw(background);
	window.draw(upArrow);
	window.draw(downArrow);
	name->Draw(window);
	weight->Draw(window);
	diameter->Draw(window);
	muzzlespeed->Draw(window);
}

void UiBullet::ReadDataBullet()
{
	const DataBullet& bulletData = BULLET_TABLE->Get(SAVEDATA_MGR.Get().selectedBullet);

	name->SetString("BulletName", " : " + bulletData.name);
	weight->SetString("BulletWeight", " : " + std::to_string(bulletData.weight) + "g");
	diameter->SetString("BulletDiameter", " : " + std::to_string(bulletData.diameter) + "mm");
	muzzlespeed->SetString("BulletMuzzleSpeed", " : " + std::to_string(bulletData.muzzleSpeed) + "m/s");
}

