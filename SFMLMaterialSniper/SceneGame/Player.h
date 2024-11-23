#pragma once
#include "SaveData.h"

class Gun;
class UiHud;
class BulletShell;

class Player : public GameObject
{
public:
	enum class PlayerStatus
	{
		Wait,
		Ready,
		Fire,
		Reloading,
	};
protected:
	
	PlayerStatus playerStatus;
	GameDefine::BreathStatus breathStatus;

	Animator animator;
	sf::Sprite body;
	SkillData skillData;

	Gun* gun;
	UiHud* uiHud;

	int ammo;
	int magazine;

	float breath;
	float maxBreath;

	float fireTimer;
	float reloadTimer;

	const sf::Vector2f muzzlePos = sf::Vector2f(2720.f, 994.f);
	const sf::Vector2f ejectionPos = sf::Vector2f(1840.f, 1056.f);

	std::function<BulletShell* ()> TakeBulletShell;

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
	void UpdateBreathStatus(float dt);
	void Draw(sf::RenderTarget& window) override;

	int GetAmmo() const { return ammo; }
	float GetBreath() const { return breath / maxBreath; }
	sf::Vector2f GetMuzzlePos() const { return body.getTransform().transformPoint(muzzlePos); }
	void SetStatus(PlayerStatus status);
};
