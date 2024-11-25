#include "stdafx.h"
#include "SceneDev2.h"
#include "Bullet.h"
#include "CircleView.h"
#include "Drum.h"
#include "RoundBoard.h"
#include "Bottle.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	SpriteGo* bg = AddGo(new SpriteGo("graphics/Stage1Background.jpg", "background"));

	bg->SetSortingLayer(SortingLayers::Background);
	bg->SetOrigin(Origins::MC);
	bullet = AddGo(new Bullet("bullet"));

	drum = AddGo(new Drum("drum"));
	roundBoard = AddGo(new RoundBoard("round"));
	bottle = AddGo(new Bottle("bottle"));

	//scopeview = AddGo(new CircleView("scope"));
	//scopeview->SetZoom(5.f);
	//scopeview->SetCircleRadius(150.f);

	Scene::Init();
}

void SceneDev2::Enter()
{
	Scene::Enter();

	sf::Vector2f screensize = FRAMEWORK.GetDefaultSize();

	drum->SetPosition({300.f,0.f,700.f});
	roundBoard->SetPosition({-300.f,0.f,700.f});
	bottle->SetPosition({0.f,0.f,700.f});
	drum->SetActive(false);
		roundBoard->SetActive(false);
		bottle->SetActive(false);

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);

	textWind.setCharacterSize(20);
	textWind.setFillColor(sf::Color::White);
	textWind.setString("Wind : " + std::to_string(wind) + "m/s");
	textWind.setPosition({ -750.f,-500.f });
	textWind.setFont(FONT_MGR.Get("fonts/malgun.ttf"));

	textMoa.setCharacterSize(20);
	textMoa.setFillColor(sf::Color::White);
	textMoa.setPosition({ -750.f,-450.f });
	textMoa.setFont(FONT_MGR.Get("fonts/malgun.ttf"));

	textBullet.setCharacterSize(20);
	textBullet.setFillColor(sf::Color::White);
	textBullet.setPosition({ -750.f,-400.f });
	textBullet.setFont(FONT_MGR.Get("fonts/malgun.ttf"));
	textBullet.setString(SAVEDATA_MGR.Get().selectedBullet);

	va.setPrimitiveType(sf::PrimitiveType::LineStrip);
}

void SceneDev2::Exit()
{
	vecText.clear();
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	textWind.setString("Wind : " + std::to_string(wind) + "m/s");


	if (fired)
	{
		firetimer += dt;
		if (firetimer > 0.2f)
		{
			firetimer = 0.f;

			sf::Vertex newpos;
			newpos.color = sf::Color::White;
			newpos.position = bullet->GetPosition();
			va.append(newpos);

			sf::Vector3f bulletpos = bullet->GetPosition3();
			sf::Vector3f bulletvel = bullet->GetVelocity3();

			sf::Text newtext;
			newtext.setCharacterSize(20);
			newtext.setFillColor(sf::Color::White);
			newtext.setString(std::to_string((int)Utils::Magnitude(startpos - bulletpos))
				+ "\n" + std::to_string((int)Utils::Magnitude(bulletvel)));
			newtext.setPosition(newpos.position);
			newtext.setFont(FONT_MGR.Get("fonts/malgun.ttf"));
			vecText.push_back(newtext);
		}
	}
	else if (firedfront)
	{
		firetimer += dt;

		if (firetimer > 0.7f && textMoa.getString() == "")
		{
			sf::Vector2f bulletpos = bullet->GetPosition();
			textMoa.setString(std::to_string((bulletpos.x - startpos.x) * 5.f) + ", " + std::to_string((bulletpos.y - startpos.y) * 5.f));
		}
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		vecText.clear();
		va.clear();
		fired = true;
		firetimer = 0.2f;

		sf::Vector2f bulletpos2f = bullet->GetPosition();
		startpos = { bulletpos2f.x,bulletpos2f.y,0.f };
		sf::Vertex newpos;
		newpos.color = sf::Color::White;
		newpos.position = bulletpos2f;
		va.append(newpos);

		auto mousepos = InputMgr::GetMousePosition();
		sf::Vector2f direction = ScreenToWorld(mousepos) - bulletpos2f;
		//direction.x *= 10.f;
		Utils::Normalize(direction);

		bullet->Fire(startpos, { direction.x,direction.y,0.f });
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		vecText.clear();
		va.clear();
		firedfront = true;
		firetimer = 0.f;

		auto mousepos = ScreenToWorld(InputMgr::GetMousePosition());
		bullet->SetPosition({ mousepos.x,mousepos.y,0.f });
		startpos = { mousepos.x,mousepos.y,0.f };
		bullet->Fire(bullet->GetPosition3());
	}
	if (InputMgr::GetMouseButtonPressing(sf::Mouse::Right))
	{
		bullet->Reset();
		fired = false;
		firedfront = false;
		textMoa.setString("");
		auto mousepos = ScreenToWorld(InputMgr::GetMousePosition());
		bullet->SetPosition({ mousepos.x,mousepos.y,0.f});
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad2))
	{
		BULLET_TABLE->Change(false);
		textBullet.setString(SAVEDATA_MGR.Get().selectedBullet);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		wind -= 1.f;
		bullet->SetWind({ wind,0.f,0.f });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		wind += 1.f;
		bullet->SetWind({ wind,0.f,0.f });
	}
	//scopeview->SetPosition(ScreenToWorld(InputMgr::GetMousePosition()));
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	const sf::View& previousView = window.getView();

	window.setView(worldView);
	window.draw(va);
	for (int i = 0; i < vecText.size();++i)
	{
		window.draw(vecText[i]);
	}

	window.setView(previousView);
	window.draw(textWind);
	window.draw(textMoa);
	window.draw(textBullet);
}
