#include "stdafx.h"
#include "UiResult.h"
#include "TextGo.h"

UiResult::UiResult(const std::string& name)
	: GameObject(name)
{
}

void UiResult::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiResult::SetRotation(float angle)
{
	rotation = angle;
}

void UiResult::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiResult::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiResult::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;

}

void UiResult::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = (int)GameDefine::UiSortingOrders::UiResult;

	txtResult = new TextGo(fontId, "result");
	txtRetry = new TextGo(fontId, "retry");
	txtTitle = new TextGo(fontId, "title");
	txtToHome = new TextGo(fontId, "tohome");
	txtResult->Init();
	txtRetry->Init();
	txtTitle->Init();
	txtToHome->Init();
}

void UiResult::Release()
{
	txtResult->Release();
	txtRetry->Release();
	txtTitle->Release();
	txtToHome->Release();
	delete txtResult;
	delete txtRetry;
	delete txtTitle;
	delete txtToHome;
}

void UiResult::Reset()
{
	active = false;

	retry.setTexture(TEXTURE_MGR.Get(buttonTexId));
	toHome.setTexture(TEXTURE_MGR.Get(buttonTexId));
	auto rect = retry.getLocalBounds();
	//retry.setTextureRect(rect);

	txtResult->Reset();
	txtRetry->Reset();
	txtTitle->Reset();
	txtToHome->Reset();
}

void UiResult::Update(float dt)
{

}

void UiResult::Draw(sf::RenderTarget& window)
{
	window.draw(titleBackground);
	window.draw(resultBackground);
	window.draw(toHome);
	window.draw(retry);

	txtResult->Draw(window);
	txtRetry->Draw(window);
	txtTitle->Draw(window);
	txtToHome->Draw(window);
}
