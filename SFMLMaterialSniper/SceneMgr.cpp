#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"

void SceneMgr::init()
{
	vecScenes.push_back(new SceneDev1());
	vecScenes.push_back(new SceneDev2());

	for (auto itScene : vecScenes)
	{
		itScene->init();
	}
	eCurrentSceneId = eDefaultSceneId;
	vecScenes[(int)eCurrentSceneId]->enter();

}

void SceneMgr::release()
{
	for (auto itscene : vecScenes)
	{
		itscene->release();
		delete itscene;
	}
	vecScenes.clear();
}

void SceneMgr::update(float fDeltaTime)
{
	vecScenes[(int)eCurrentSceneId]->update(fDeltaTime);
}

void SceneMgr::draw(sf::RenderWindow& window)
{
	vecScenes[(int)eCurrentSceneId]->draw(window);
}

void SceneMgr::setCurrentScene(SceneIds iSceneId)
{
	vecScenes[(int)eCurrentSceneId]->exit();
	eCurrentSceneId = iSceneId;
	vecScenes[(int)eCurrentSceneId]->enter();
}
