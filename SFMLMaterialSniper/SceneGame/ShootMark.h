#pragma once

class GameObject;

class ShootMark : public GameObject
{
protected:

	std::vector<sf::Color> colors;
	std::vector<sf::VertexArray> arrows;
	std::vector<sf::Vector2f> vertexPos;

	GameObject* obj;

	int offsety;
	int index;
	float timer;
	float duration;

public:
	ShootMark(const std::string& name = "");
	~ShootMark() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetOffset(const sf::Vector2f& disp) override;
	void SetFlipX(bool flipX) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void OnHit();
};
