#pragma once

class HelpMessage : public GameObject
{
protected:

	sf::Sprite body;
	Animator animator;

	float timer;
	float duration;

public:
	HelpMessage(const std::string& name = "");
	~HelpMessage() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetOffset(const sf::Vector2f& disp) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void StartTimer(float duration);
};
