#pragma once

class TextGo;

class UiBullet : public GameObject
{
protected:

	sf::RectangleShape background;

	TextGo* name;
	TextGo* weight;
	TextGo* diameter;
	TextGo* muzzlespeed;
	sf::Vector2f offsetName;
	sf::Vector2f offsetWeight;
	sf::Vector2f offsetDiameter;
	sf::Vector2f offsetMuzzlespeed;
	std::string fontId;

	sf::Sprite upArrow;
	sf::Vector2f offsetUpArrow;
	sf::Sprite downArrow;
	sf::Vector2f offsetDownArrow;
	std::string texId;
	sf::Vector2i textureRect;

public:
	UiBullet(const std::string& name = "");
	~UiBullet() = default;

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

	void ReadDataBullet();
};
