#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "CloudGo.h"
#include "BeeGo.h"
#include "TreeGo.h"
#include "PlayerGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

SceneDev1::SceneDev1()
	:Scene(SceneIds::Dev1)
{
}

void SceneDev1::init()
{
	std::cout << "SceneDev1::init()" << std::endl;

	ResourceMgr<sf::Texture>::Instance().load("graphics/player.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/rip.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/axe.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/tree.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/branch.png");

	auto sprBG = addGo(new SpriteGo("graphics/background.png", "BackGround"));

	auto txtScene = addGo(new TextGo("fonts/KOMIKAP_.ttf", "SceneDev1"));

	for (int i = 0;i < 3;++i)
	{
		CloudGo* cobj = addGo(new CloudGo("graphics/cloud.png"));
		cobj->setBounds({ -300.f,2200.f });
	}

	ptrTree = addGo(new TreeGo("Tree"));
	ptrPlayer = addGo(new PlayerGo("Player"));

	txtCenterMessage = addGo(new TextGo("fonts/KOMIKAP_.ttf", "CenterMessage"));
	uiScore = addGo(new UiScore("fonts/KOMIKAP_.ttf","UIScore"));
	uiTimebar = addGo(new UiTimebar("UITimebar"));

	for (int i = 0;i < 3;++i)
	{
		BeeGo* bobj = addGo(new BeeGo("graphics/bee.png"));
		bobj->setBounds({ -300.f,2200.f });
	}

	Scene::init();

	ptrTree->setPosition({ 1920.f * 0.5f, 900.f });
	ptrPlayer->setPosition({ 1920.f * 0.5f, 900.f });
	sprBG->setOrigin(Origins::MC);
	sprBG->setPosition({ 1920.f * 0.5f, 1080.f * 0.5f });

	txtScene->setOrigin(Origins::MC);
	txtScene->setPosition({ 100.f, 100.f });

	txtCenterMessage->setCharSize(100);
	txtCenterMessage->setTextColor(sf::Color::Red);
	txtCenterMessage->setOrigin(Origins::MC);
	txtCenterMessage->setPosition({ 1920.f * 0.5f, 1080.f * 0.5f });

	uiScore->setCharSize(40);
	uiScore->setTextColor(sf::Color::White);
	uiScore->setPosition({ 1920.f * 0.01f, 1080.f * 0.01f });

	uiTimebar->setOrigin(Origins::ML);
	uiTimebar->setTimebar({500.f,100.f},sf::Color::Red);
	uiTimebar->setPosition({ 1920.f * 0.5f-250.f, 1080.f * 0.9f });
}

void SceneDev1::enter()
{
	std::cout << "SceneDev1::enter()" << std::endl;

	ResourceMgr<sf::Texture>::Instance().load("graphics/log.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/tree.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/branch.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/background.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/cloud.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/bee.png");
	ResourceMgr<sf::Font>::Instance().load("fonts/KOMIKAP_.ttf");

	Scene::enter();
	ptrPlayer->setScene(this);
	setStatus(Status::Awake);
}

void SceneDev1::exit()
{
	std::cout << "SceneDev1::exit()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/log.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/tree.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/branch.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/background.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/cloud.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/bee.png");
	ResourceMgr<sf::Font>::Instance().unload("fonts/KOMIKAP_.ttf");
}

void SceneDev1::update(float dt)
{
	Scene::update(dt);

	if (InputMgr::isKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().setCurrentScene(SceneIds::Dev2);
	}

	switch (eStatus)
	{
	case Status::Awake:
		updateAwake(dt);
		break;
	case Status::GameOver:
		updateGameOver(dt);
		break;
	case Status::InGame:
		updateInGame(dt);
		break;
	case Status::Pause:
		updatePause(dt);
		break;
	}
}

void SceneDev1::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}

void SceneDev1::setCenterMessage(const std::string& iMessage)
{
	txtCenterMessage->setString(iMessage);
}

void SceneDev1::setVisibleCenterMessage(bool iVisible)
{
	txtCenterMessage->setDraw(iVisible);
}

void SceneDev1::setScore(int iScore)
{
	dScore = iScore;
	uiScore->setScore(dScore);
}

void SceneDev1::setStatus(Status iStatus)
{
	Status prvStatus = eStatus;
	eStatus = iStatus;
	switch (eStatus)
	{
	case Status::Awake:
		Framework::Instance().setTimeScale(0.f);
		setVisibleCenterMessage(true);
		setCenterMessage("Press Enter To Start");
		setScore(0);
		fGameTime = fMaxGameTime;
		uiTimebar->setValue(1.f);
		break;
	case Status::InGame:
		if (prvStatus == Status::GameOver)
		{
			setScore(0);
			fGameTime = fMaxGameTime;
			uiTimebar->setValue(1.f);

			ptrPlayer->reset();
			ptrTree->reset();
		}
		Framework::Instance().setTimeScale(1.f);
		setVisibleCenterMessage(false);

		break;
	case Status::GameOver:
		Framework::Instance().setTimeScale(0.f);
		setVisibleCenterMessage(true);
		break;
	case Status::Pause:
		Framework::Instance().setTimeScale(0.f);
		setCenterMessage("PAUSED! ESC TO RESUME");
		setVisibleCenterMessage(true);
		break;
	}
}

void SceneDev1::updateAwake(float dt)
{
	if (InputMgr::isKeyDown(sf::Keyboard::Enter))
	{
		setStatus(Status::InGame);
	}
}

void SceneDev1::updateInGame(float dt)
{
	if (InputMgr::isKeyDown(sf::Keyboard::Escape))
	{
		setStatus(Status::Pause);
		return;
	}

	fGameTime = Utilities::clamp(fGameTime -= dt, 0.f, fMaxGameTime);
	uiTimebar->setValue(fGameTime / fMaxGameTime);
	if (fGameTime <= 0.f)
	{
		ptrPlayer->onDie();
		setCenterMessage("TIME OVER!!!");
		setStatus(Status::GameOver);
		return;
	}
}

void SceneDev1::updateGameOver(float dt)
{
	if (InputMgr::isKeyDown(sf::Keyboard::Enter))
	{
		setStatus(Status::InGame);
	}
}

void SceneDev1::updatePause(float dt)
{
	if (InputMgr::isKeyDown(sf::Keyboard::Escape))
	{
		setStatus(Status::InGame);
	}
}

void SceneDev1::OnChop(Sides iSide)
{
	Sides branchSide = ptrTree->chop(iSide);
	if (ptrPlayer->getSide() == branchSide)
	{
		ptrPlayer->onDie();
		setCenterMessage("You Died");
		setStatus(Status::GameOver);
	}
	else
	{
		setScore(dScore + 100);
		fGameTime = Utilities::clamp(fGameTime + 1.f, 0.f, fMaxGameTime);
	}
}
