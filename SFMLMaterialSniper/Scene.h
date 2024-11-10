#pragma once
class Scene
{
protected:
	const SceneIds eSceneId;

	std::list<GameObject*> lstGameObj;
	
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
public:
	Scene(SceneIds iSceneId);
	virtual ~Scene() = default;

	virtual void init();
	virtual void release();

	virtual void enter();
	virtual void exit();

	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

	template<typename T>
	T* addGo(T* obj)
	{
		if (std::find(lstGameObj.begin(), lstGameObj.end(), obj) == lstGameObj.end())
		{
			lstGameObj.push_back(obj);
		}
		return obj;
	}

	virtual void removeGo(GameObject* obj);

	template<typename T>
	void removeGo(std::list<T*> lstobj)
	{
		for (auto obj : lstobj)
		{
			lstGameObj.remove(obj);
		}
	}

	virtual GameObject* findGo(const std::string& iName);
	virtual int FindGoAll(const std::string& iName, std::list<GameObject*>& lstFoundGo);
};

