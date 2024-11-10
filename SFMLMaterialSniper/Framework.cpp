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

#pragma region �̺�Ʈ ó�� ����
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

#pragma region ��ü ������Ʈ

		SceneMgr::Instance().update(fGameDT);

#pragma endregion

#pragma region ��ü ��ο�
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
