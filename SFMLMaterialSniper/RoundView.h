#pragma once
class RoundView
{
protected:
	sf::RenderTexture renderTexture;
	sf::View renderView;
	sf::CircleShape rendermask;
	

	float zoom;
	float maskRadius;
	sf::Vector2u textureSize;
	sf::Vector2f renderViewCenter;
	

	bool gameObjectsChanged;
	std::list<GameObject*> drawObjects;
	std::list<GameObject*> removeGameObjs;
	std::list<GameObject*> addGameObjs;
	//sf::FloatRect 

public:

	RoundView();
	virtual ~RoundView() = default;

	virtual void SetZoom(float zoom);
	virtual void SetViewPort(const sf::FloatRect& ratioRect);
	virtual void SetViewPort(const sf::Vector2f& displaySize, const sf::FloatRect& pixelRect);
	virtual void SetViewCenter(const sf::Vector2f& center);

	virtual void SetViewSize(const sf::Vector2f& region);

	template<typename T>
	T* AddGo(T* obj)
	{
		gameObjectsChanged = true;
		addGameObjs.push_back(obj);
		return obj;
	}

	virtual void RemoveGo(GameObject* obj);

	template<typename T>
	void RemoveGo(std::list<T*> lstobj)
	{
		gameObjectsChanged = true;
		for (auto obj : lstobj)
		{
			removeGameObjs.push_back(obj);
		}
	}

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float dt);

	virtual void OnPreDraw();
	virtual void Draw(sf::RenderWindow& window);

	virtual void ApplyAddGo();
	virtual void ApplyRemoveGo();
	virtual void SortDrawObject();
	//void Set
};

