#include "stdafx.h"
#include "UiResult.h"
#include "TextGo.h"
#include "SceneGame.h"
#include "ButtonRound.h"

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
	btnRetry = new ButtonRound("retry");
	txtTitle = new TextGo(fontId, "title");
	btnGohome = new ButtonRound("tohome");
	txtResult->Init();
	btnRetry->Init();
	txtTitle->Init();
	btnGohome->Init();
}

void UiResult::Release()
{
	txtResult->Release();
	btnRetry->Release();
	txtTitle->Release();
	btnGohome->Release();
	delete txtResult;
	delete btnRetry;
	delete txtTitle;
	delete btnGohome;
}

void UiResult::Reset()
{
	active = false;

	txtResult->Reset();
	btnRetry->Reset();
	txtTitle->Reset();
	btnGohome->Reset();
	resetTime = FRAMEWORK.GetRealTime();

	sf::Vector2f screensize = FRAMEWORK.GetDefaultSize();

	titleBackground.setSize({ 1280.f, 700.f });
	Utils::SetOrigin(titleBackground, Origins::TC);
	titleBackground.setPosition({ screensize.x * 0.5f,120.f });
	titleBackground.setFillColor({ 0,0,0,100 });

	txtTitle->SetString("Result", true);
	txtTitle->SetPosition({ screensize.x * 0.5f,180.f });
	txtTitle->SetOrigin(Origins::MC);
	txtTitle->SetColor(sf::Color::White);
	txtTitle->SetCharSize(70.f);

	btnRetry->SetPosition({ screensize.x * 0.3f,screensize.y * 0.85f });
	btnRetry->SetString("Retry", true);
	btnRetry->SetScale({ 2.f,2.f });
	btnRetry->SetCharSize(40.f);

	btnGohome->SetPosition({ screensize.x * 0.7f,screensize.y * 0.85f });
	btnGohome->SetString("Gohome", true);
	btnGohome->SetScale({ 2.f,2.f });
	btnGohome->SetCharSize(40.f);

	txtResult->SetPosition(screensize * 0.5f);
	txtResult->SetOrigin(Origins::MC);
	txtResult->SetColor(sf::Color::White);
	txtResult->SetCharSize(50.f);

	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		btnRetry->SetClicked([scene]() {scene->SetStatus(GameDefine::SceneStatus::Awake); });
		btnGohome->SetClicked([]() {SCENE_MGR.ChangeScene(SceneIds::Home); });
	}
}

void UiResult::Update(float dt)
{
	txtResult->Update(dt);
	btnRetry->Update(dt);
	txtTitle->Update(dt);
	btnGohome->Update(dt);
}

void UiResult::Draw(sf::RenderTarget& window)
{
	window.draw(titleBackground);
	window.draw(resultBackground);

	txtResult->Draw(window);
	btnRetry->Draw(window);
	txtTitle->Draw(window);
	btnGohome->Draw(window);
}

void UiResult::ShowResult()
{
	txtResult->SetString(L"스킬 포인트 10 획득\n현재 스킬포인트 : "+std::to_wstring(SAVEDATA_MGR.Get().skillData.skillPoint));
}
