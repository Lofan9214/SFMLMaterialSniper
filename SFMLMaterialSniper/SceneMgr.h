#pragma once
#include "Scene.h"

class SceneMgr : public Singleton<SceneMgr>
{
	friend Singleton<SceneMgr>;
protected:
	std::vector<Scene*> vecScenes;

	SceneIds eDefaultSceneId = SceneIds::Dev1;
	SceneIds eCurrentSceneId;

	SceneMgr() = default;
	virtual ~SceneMgr() = default;

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;

public:

	void init();
	void release();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	Scene* getCurrentScene() { return vecScenes[(int)eCurrentSceneId]; }
	SceneIds getCurrentSceneId() const { return eCurrentSceneId; }
	void setCurrentScene(SceneIds id);

};

