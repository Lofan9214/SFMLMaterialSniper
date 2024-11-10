#include "stdafx.h"
#include "SceneDev2.h"

SceneDev2::SceneDev2()
	:Scene(SceneIds::Dev2)
{
}

void SceneDev2::init()
{
	Scene::init();


}

void SceneDev2::enter()
{

	Scene::enter();
}

void SceneDev2::exit()
{

	Scene::exit();
}

void SceneDev2::update(float dt)
{
	if (InputMgr::isKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().setCurrentScene(SceneIds::Dev1);
	}

	Scene::update(dt);
}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
