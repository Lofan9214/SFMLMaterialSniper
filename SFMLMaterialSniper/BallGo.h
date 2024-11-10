#pragma once
#include "GameObject.h"

class BatGo;

class BallGo :
	public GameObject
{
protected:
	sf::CircleShape body;

	sf::Vector2f direction = { 0.f,0.f };
	float speed = 0.f;

	sf::FloatRect movableBounds = { 0.f,0.f,0.f,0.f };

	BatGo* bat;

	bool hitBottom = false;
	bool hitBat = false;

public:
	BallGo(const std::string& name = "");
	virtual ~BallGo() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;

	void Reset() override;

	void Release() override;

	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;
	void Draw(sf::RenderTexture& texture) override;

	void SetBat(BatGo* bat) { this->bat = bat; }

	void Fire(const sf::Vector2f& direction, float speed)
	{
		this->direction = direction;
		this->speed = speed;
	}

	bool GetHitBottom() const;
	void ResetHitBottom();

	bool GetHitBat() const;
	void ResetHitBat();
};

