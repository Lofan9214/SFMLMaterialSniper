#pragma once

class BulletShell : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/bullet/bulletshell.png";

	sf::Vector2f velocity;
	sf::Vector2f screensize;

	float gravity;
	float ejectionTimer;
	float ejectionAngle;

	std::function<void(BulletShell*)> ReturnBulletShell;

public:
	BulletShell(const std::string& name = "");
	~BulletShell() = default;

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

	void Eject(const sf::Vector2f& pos);
};
