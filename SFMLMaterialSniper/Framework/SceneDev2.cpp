#include "stdafx.h"
#include "SceneDev2.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	Scene::Init();

}

void SceneDev2::Enter()
{
	Scene::Enter();

	sf::Vector2f screensize = FRAMEWORK.GetWindowSizef();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);

	bullet.setRadius(5.f);
	bullet.setFillColor(sf::Color::White);
	bullet.setOrigin(5.f, 5.f);

	textWind.setCharacterSize(20);
	textWind.setFillColor(sf::Color::White);
	textWind.setString("Wind : " + std::to_string(wind) + "m/s");
	textWind.setPosition({ -900.f,-500.f });
	textWind.setFont(FONT_MGR.Get("malgun.ttf"));

	textMoa.setCharacterSize(20);
	textMoa.setFillColor(sf::Color::White);
	textMoa.setPosition({ -900.f,-450.f });
	textMoa.setFont(FONT_MGR.Get("malgun.ttf"));

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
			newpos.position = bullet.getPosition();
			va.append(newpos);

			sf::Text newtext;
			newtext.setCharacterSize(20);
			newtext.setFillColor(sf::Color::White);
			newtext.setString(std::to_string((int)Utils::Magnitude(startpos - bulletpos))
				+ "\n" + std::to_string((int)Utils::Magnitude(bulletvel)));
			newtext.setPosition(bullet.getPosition());
			newtext.setFont(FONT_MGR.Get("malgun.ttf"));
			vecText.push_back(newtext);
		}

		sf::Vector3f force;

		force = -(0.5f) * (0.295f) * (1.2f) * (Utils::PI) * (0.25f) * (7.82f * 0.001f) * (7.82f * 0.001f) * (bulletvel)*Utils::Magnitude(bulletvel);

		// F = -C*rho*A*abs(V-W)*(V-W)/2
		// C : 항력 계수 (일반적인 상황에서 0.295)
		// rho : 공기 저항
		// A : 탄두의 단면적
		// V : 탄두의 속도
		// W : 바람의 속도

		bulletacc = force / (11.3f * 0.001f);
		bulletacc.y += 9.8f;
		bulletvel += bulletacc * dt;
		bulletpos += bulletvel * dt;
		bullet.setPosition(bulletpos.x, bulletpos.y);
	}
	else if (firedfront)
	{
		sf::Vector3f force;
		sf::Vector3f velwithwin = bulletvel - sf::Vector3f(wind, 0.f, 0.f);
		firetimer += dt;


		force = -(0.5f) * (0.295f) * (1.2f) * (Utils::PI) * (0.25f) * (7.82f * 0.001f) * (7.82f * 0.001f) * (velwithwin)*Utils::Magnitude(velwithwin);

		// F = -C*rho*A*abs(V-W)*(V-W)/2
		// C : 항력 계수 (일반적인 상황에서 0.295)
		// rho : 공기 저항
		// A : 탄두의 단면적
		// V : 탄두의 속도
		// W : 바람의 속도

		bulletacc = force / (11.3f * 0.001f);
		bulletacc.y += 49.f;
		bulletvel += bulletacc * dt;
		bulletpos += bulletvel * dt;
		bullet.setPosition(bulletpos.x, bulletpos.y);
		if (firetimer>0.7f && textMoa.getString() == "")
		{
			textMoa.setString(std::to_string((bulletpos.x - startpos.x) * 5.f) + ", " + std::to_string((bulletpos.y - startpos.y) * 5.f));
		}
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		vecText.clear();
		va.clear();
		fired = true;
		firetimer = 0.2f;

		sf::Vector2f bulletpos2f = bullet.getPosition();
		//bulletpos->x = bulletpos2f.x * 10.f;
		bulletpos.x = bulletpos2f.x;
		bulletpos.y = bulletpos2f.y;
		bulletpos.z = 0.f;
		startpos = bulletpos;
		sf::Vertex newpos;
		newpos.color = sf::Color::White;
		newpos.position = bullet.getPosition();
		va.append(newpos);

		auto mousepos = InputMgr::GetMousePosition();
		sf::Vector2f direction = ScreenToWorld(mousepos) - bullet.getPosition();
		//direction.x *= 10.f;
		Utils::Normalize(direction);

		bulletvel.x = direction.x * 790.f;
		bulletvel.y = direction.y * 790.f;
		bulletvel.z = 0.f;
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		vecText.clear();
		va.clear();
		firedfront = true;
		firetimer = 0.f;
		sf::Vector2f bulletpos2f = bullet.getPosition();
		bulletpos.x = bulletpos2f.x;
		bulletpos.y = bulletpos2f.y;
		bulletpos.z = 0.f;
		startpos = bulletpos;

		bulletvel.x = 0.f;
		bulletvel.y = 0.f;
		bulletvel.z = 790.f;
	}
	if (InputMgr::GetMouseButtonPressing(sf::Mouse::Right))
	{
		fired = false;
		firedfront = false;
		textMoa.setString("");
		auto mousepos = InputMgr::GetMousePosition();
		bullet.setPosition(ScreenToWorld(mousepos));
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		wind -= 1.f;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		wind += 1.f;
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	const sf::View& previousView = window.getView();

	window.setView(worldView);
	window.draw(va);
	window.draw(bullet);
	for (int i = 0; i < vecText.size();++i)
	{
		window.draw(vecText[i]);
	}

	window.setView(previousView);
	window.draw(textWind);
	window.draw(textMoa);
}
