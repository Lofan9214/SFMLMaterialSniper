#pragma once

class TextGo;

class UiSkill : public GameObject
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

	std::vector<sf::Sprite> upArrows;
	std::vector<sf::Sprite> downArrows;
	std::vector<std::vector<sf::Sprite>> stars;
	sf::Vector2f offsetUpArrow;
	sf::Vector2f offsetDownArrow;
	sf::Vector2f offsetArrowGroup;
	std::string texId;
	sf::Vector2i textureRect;

public:
	UiSkill(const std::string& name = "");
	~UiSkill() = default;

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

	void ButtonsUpdate();
	void SkillUpDown(int index, bool up);
};
