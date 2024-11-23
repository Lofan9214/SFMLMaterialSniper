#pragma once

class Bullet;
class CircleView;
class Player;
class UiHud;

class Gun : public GameObject
{
protected:
	Animator animator;
	sf::Sprite body;
	sf::Sprite muzzlefire;

	CircleView* circleView;
	Player* player;
	UiHud* uiHud;
	
	bool drawbody;
	bool drawmuzzlefire;

	sf::Vector2f scopePos;
	sf::Vector2f scopeVibration;
	sf::Vector2f vibrationScale;
	sf::Vector2f vibrationScaleOrigin;
	float vibrationSpeed = 1.f;
	float vibrationTimer = 0.f;

	sf::Vector2f scopeRecoil;
	sf::Vector2f scopeRecoilDir1;
	sf::Vector2f scopeRecoilDir2;
	float recoilTimer;
	float firstRecoil;
	float secondRecoil;
	const float firetobolt = 0.13f;

	GameDefine::BreathStatus breathStatus;
	GameDefine::RecoilStatus boltStatus;

	std::function<void()> ScreenRecoil;
	std::function<Bullet* ()> TakeBullet;

public:
	Gun(const std::string& name = "");
	~Gun() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetOffset(const sf::Vector2f& disp) override;
	void SetColor(const sf::Color& color) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateScopePosition(float dt);
	void UpdateScopeRecoil(float dt);
	void UpdateScopeVibration(float dt);
	void Draw(sf::RenderTarget& window) override;

	void SetScope(int scopeSize);
	void SetRecoilScale(int control);

	void SetRecoilStatus(GameDefine::RecoilStatus state);
	void SetBreathStatus(GameDefine::BreathStatus state);
	void Fire();
};
