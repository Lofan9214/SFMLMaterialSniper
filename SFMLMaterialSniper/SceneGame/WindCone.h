#pragma once

class WindCone : public GameObject
{
protected:

	sf::Sprite body;
	Animator animator;
public:
	WindCone(const std::string& name = "");
	~WindCone() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetDisplacement(const sf::Vector2f& disp) override;
	void SetFlipX(bool flipX) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void SetWindSpeed(int speed);
};
