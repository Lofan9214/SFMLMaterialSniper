#pragma once

class Bullet;

class Drum : public GameObject
{
protected:

	sf::Sprite body;
	Animator animator;

	Bullet* bullet;

	sf::Vector3f position3;
	float defaultdistance = 800.f;
	std::function<void()> TargetHit;

public:
	Drum(const std::string& name = "");
	~Drum() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetPosition(const sf::Vector3f& pos);
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetDisplacement(const sf::Vector2f& disp) override;
	void SetColor(const sf::Color& color) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override { return body.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderTarget& window) override;
};
