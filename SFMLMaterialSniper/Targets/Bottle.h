#pragma once

class Bullet;

class Bottle : public GameObject
{
protected:

	std::string texId = "graphics/targets/bottle.png";
	sf::Sprite body;

	Bullet* bullet;

	sf::Vector3f position3;
	float defaultdistance = 100.f;

public:
	Bottle(const std::string& name = "");
	~Bottle() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetPosition(const sf::Vector3f& pos);
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

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

