#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds iSceneId)
	:eSceneId(iSceneId)
{
}

void Scene::init()
{
	for (auto obj : lstGameObj)
	{
		obj->init();
	}
}

void Scene::release()
{
	for (auto obj : lstGameObj)
	{
		obj->release();
		delete obj;
	}
	lstGameObj.clear();
}

void Scene::enter()
{
	for (auto obj : lstGameObj)
	{
		obj->reset();
	}
}

void Scene::exit()
{
}

void Scene::update(float dt)
{
	for (auto obj : lstGameObj)
	{
		if (!obj->getActive())
		{
			continue;
		}
		obj->update(dt);
	}
}

void Scene::draw(sf::RenderWindow& window)
{
	for (auto obj : lstGameObj)
	{
		if (!obj->getDraw())
		{
			continue;
		}
		obj->draw(window);
	}

}

void Scene::removeGo(GameObject* obj)
{
	if (find(lstGameObj.begin(), lstGameObj.end(), obj)!=lstGameObj.end())
	{
		delete obj;
		lstGameObj.remove(obj);
	}
}

GameObject* Scene::findGo(const std::string& iName)
{
	for (auto obj : lstGameObj)
	{
		if (obj->getName() == iName)
		{
			return obj;
		}
	}
	return nullptr;
}

int Scene::FindGoAll(const std::string& iName, std::list<GameObject*>& lstFoundGo)
{
	int cnt = 0;

	if (lstFoundGo.size() > 0)
	{
		for (auto obj : lstFoundGo)
		{
			obj->release();
		}
		lstFoundGo.clear();
	}

	for (auto obj : lstGameObj)
	{
		if (obj->getName() == iName)
		{
			++cnt;
			lstFoundGo.push_back(obj);
		}
	}

	return cnt;
}


