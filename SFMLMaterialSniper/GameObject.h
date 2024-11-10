#pragma once

class GameObject
{
protected:
	bool bActive = true;
	bool bDraw = true;

	std::string strName;

	Origins eOrigin;
	sf::Vector2f vOrigin;
	sf::Vector2f vPosition;
	float fRotation;
	sf::Vector2f vScale;
	bool bFlipX = false;
	bool bFlipY = false;


	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

public:
	GameObject(const std::string& iName = "");
	virtual ~GameObject() = default;

	virtual void init();
	virtual void release();

	virtual void reset();

	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

	bool getActive() const { return bActive; }
	void setActive(bool iActive) { bActive = iActive; }

	bool getDraw() const { return bDraw; }
	void setDraw(bool iDraw) { bDraw = iDraw; }

	const std::string& getName() { return strName; }
	void setName(const std::string& iName) { strName = iName; }

	sf::Vector2f getOrigin() const { return vOrigin; }
	virtual void setOrigin(Origins iOrigin);
	virtual void setOrigin(const sf::Vector2f& iOrigin)
	{
		vOrigin = iOrigin;
		eOrigin = Origins::Custom;
	}

	sf::Vector2f getPosition() const { return vPosition; }
	virtual void setPosition(const sf::Vector2f& iPosition) { vPosition = iPosition; }

	float getRotation() const { return fRotation; }
	void setRotation(float iRotation) { fRotation = iRotation; }

	sf::Vector2f getScale() const { return vScale; }
	virtual void setScale(const sf::Vector2f& iScale) { vScale = iScale; }

	virtual bool getFlipX() const { return bFlipX; }
	virtual void setFlipX(bool flipx);
	virtual bool getFlipY() const { return bFlipY; }
	virtual void setFlipY(bool flipy);

};

