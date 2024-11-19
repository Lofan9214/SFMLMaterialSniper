#pragma once

class Bullet;
class CircleView;
class Player;

class Gun : public GameObject
{
protected:

	Animator animator;
	sf::Sprite body;
	sf::Sprite muzzlefire;

	Bullet* bullet;
	CircleView* circleView;
	Player* player;
	
	bool drawbody;
	bool drawmuzzlefire;

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

	bool breathover;

public:
	Gun(const std::string& name = "");
	~Gun() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetDisplacement(const sf::Vector2f& disp) override;
	void SetColor(const sf::Color& color) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateScopePosition(float dt);
	void UpdateScopeVibration(float dt);
	void Draw(sf::RenderTarget& window) override;

	void NextRoad();
	void SetScope(int scopeSize);
	void SetRecoilSpeed(int control);
	void SetBreathover(bool over) { breathover = over; }
	void SetVibrationSpeed(float speed) { vibrationSpeed = speed; }
	void Fire();
};
