#include "stdafx.h"

void Framework::Init(int width, int height, const std::string& name)
{
	window.create(sf::VideoMode(width, height), name);

	Utils::Init();
	DATATABLE_MGR.Init();
	SCENE_MGR.Init();
	SOUND_MGR.Init();
	InputMgr::Init();
}

void Framework::Do()
{
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		realDeltaTime = deltaTime = dt.asSeconds();
		deltaTime *= timeScale;
		realTime += realDeltaTime;
		time += deltaTime;

#pragma region 이벤트 루프
		InputMgr::Clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//if (event.type == sf::Event::Resized)
			//{
			//	SCENE_MGR.GetCurrentScene()->SetWorldView(event.size.width, event.size.height);
			//}

			InputMgr::UpdateEvent(event);
		}
#pragma endregion

#pragma region 업데이트
		InputMgr::Update(deltaTime);
		SCENE_MGR.Update(deltaTime);
		SCENE_MGR.LateUpdate(deltaTime);
		SCENE_MGR.FixedUpdate(deltaTime);
#pragma endregion

#pragma region 드로우
		window.clear();
		SCENE_MGR.Draw(window);
		window.display();
#pragma endregion
	}
}

void Framework::Release()
{
	SCENE_MGR.Release();
	SOUND_MGR.Release();
	DATATABLE_MGR.Release();
}