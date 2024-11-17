#pragma once
#include "SaveData.h"

class Bullet;
class CircleView;

class Player : public GameObject
{
protected:

	std::string texId;
	sf::Sprite body;
	SkillData skill;

	Bullet* bullet;
	CircleView* circleView;

	sf::Vector2f scopeVibration;
	sf::Vector2f vibrationScale;
	float vibrationSpeed = 1.f;
	float vibrationTimer = 0.f;

	int ammo;
	int clip = 5;
	float breath;
	float maxBreath = 2.7;

public:
	Player(const std::string& name = "");
	~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void SetCircleView(CircleView* circleView) { this->circleView = circleView; }
	void SetVibrationSpeed(float speed) { vibrationSpeed = speed; }
	void UpdateScopeVibration(float dt);

	int GetAmmo() const { return ammo; }
	float GetBreath() const { return breath/maxBreath; }
};
