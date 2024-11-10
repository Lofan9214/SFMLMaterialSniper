#include "stdafx.h"
#include "Framework.h"

void Framework::init(int iWidth, int iHeight, const std::string& strTitle)
{
	window.create(sf::VideoMode(iWidth, iHeight), strTitle);

	Utilities::init();

	SceneMgr::Instance().init();
}

void Framework::dothis()
{
	sf::Event ev;
	sf::Time dt;

	while (window.isOpen())
	{
		dt = clock.restart();
		fRealDT = fGameDT = dt.asSeconds();
		fGameDT *= fTimeScale;
		fRealTime += fRealDT;
		fGameTime += fGameDT;

#pragma region 이벤트 처리 루프
		InputMgr::clear();
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}

			InputMgr::updateEvent(ev);
		}
#pragma endregion

#pragma region 객체 업데이트

		SceneMgr::Instance().update(fGameDT);

#pragma endregion

#pragma region 객체 드로우
		window.clear();

		SceneMgr::Instance().draw(window);

		window.display();
#pragma endregion
	}
}

void Framework::release()
{
	SceneMgr::Instance().release();
}
