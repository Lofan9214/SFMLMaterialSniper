#pragma once
#include "GameObject.h"
class BatGo :
    public GameObject
{
protected:

	sf::RectangleShape body;

	sf::Vector2f direction = { 0.f,0.f };
	float speed = 500.f;

	sf::Vector2f initPos = { 0.f,0.f };

	float minX;
	float maxX;

public:

	BatGo(const std::string& name = "");
	virtual ~BatGo() = default;

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

	void Draw(sf::RenderTarget& renderTarget) override;
	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
};

