#pragma once
class GameObject
{
protected:
	std::string name;
	bool active = true;

	float rotation;

	sf::Vector2f position;
	sf::Vector2f scale;
	Origins originPreset;
	sf::Vector2f origin;
	HitBox hitBox;

	bool bFlipX = false;
	bool bFlipY = false;

	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;
	int targetView = 0;

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

public:
	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;

	const std::string& GetName() { return name; }
	void SetName(const std::string& iname) { name = iname; }

	bool IsActive() const { return active; }
	void SetActive(bool bActive) { active = bActive; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& neworigin)
	{
		origin = neworigin;
		originPreset = Origins::Custom;
	}

	virtual sf::FloatRect GetLocalBounds() const { return { 0.f,0.f,0.f,0.f }; }
	virtual sf::FloatRect GetGlobalBounds() const { return { 0.f,0.f,0.f,0.f }; }

	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& iscale) { scale = iscale; }

	virtual bool GetFlipX() const { return bFlipX; }
	virtual void SetFlipX(bool flipx);
	virtual bool GetFlipY() const { return bFlipY; }
	virtual void SetFlipY(bool flipy);

	float GetRotation() const { return rotation; }
	virtual void SetRotation(float angle) { rotation = angle; }

	virtual const HitBox& GetHitBox() const { return hitBox; }

	virtual HitBox& GetHitBox() { return hitBox; }

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Reset() = 0;

	virtual void Update(float dt) = 0;
	virtual void LateUpdate(float dt) {}
	virtual void FixedUpdate(float dt) {}
	virtual void Draw(sf::RenderTarget& window) = 0;

	void SetSortingLayer(SortingLayers sortingLayer) { this->sortingLayer = sortingLayer; }
	SortingLayers GetSortingLayer() { return sortingLayer; }

	void SetSortingOrder(int sortingOrder) { this->sortingOrder = sortingOrder; }
	int GetSortingOrder() { return this->sortingOrder; }
};

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b) const
	{
		SortingLayers sortingLayerA = a->GetSortingLayer();
		SortingLayers sortingLayerB = b->GetSortingLayer();

		if (sortingLayerA != sortingLayerB)
			return sortingLayerA > sortingLayerB;
		return a->GetSortingOrder() > b->GetSortingOrder();
	}
};