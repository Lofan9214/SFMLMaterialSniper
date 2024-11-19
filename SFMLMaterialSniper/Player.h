#pragma once
#include "SaveData.h"

class Bullet;
class CircleView;

class Player : public GameObject
{
public:
	enum class Status
	{
		Ready,
		Fire,
		Reloading,
	};

protected:

	Status status;

	Animator animator;
	sf::Sprite body;
	SkillData skillData;

	Bullet* bullet;
	CircleView* circleView;

	sf::Vector2f scopePos;
	sf::Vector2f scopeVibration;
	sf::Vector2f vibrationScale;
	sf::Vector2f vibrationScaleOrigin;
	float vibrationSpeed = 1.f;
	float vibrationTimer = 0.f;

	sf::Vector2f scopeRecoil;
	sf::Vector2f scopeRecoilVel;
	float recoilSpeed;
	float boltrecoilSpeed;

	int ammo;
	int magazine;
	
	float breath;
	float maxBreath;
	bool breathover;
	
	float fireTimer;
	float reloadTimer;

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
	void UpdateReady(float dt);
	void UpdateFire(float dt);
	void UpdateReload(float dt);
	void UpdateScopePosition(float dt);
	void UpdateBreathStatus(float dt);
	void Draw(sf::RenderTarget& window) override;

	void SetVibrationSpeed(float speed) { vibrationSpeed = speed; }
	void SetStatus(Status status);

	int GetAmmo() const { return ammo; }
	float GetBreath() const { return breath / maxBreath; }
};
