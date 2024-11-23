#pragma once

class TextGo;

class UiSkill : public GameObject
{
protected:
	sf::RectangleShape background;

	TextGo* title;
	std::vector<TextGo*> names;
	std::vector<std::string> skillNames;
	TextGo* manual;
	TextGo* skillpoint;
	TextGo* skillpoint2;

	sf::Vector2f offsetTitle;
	sf::Vector2f offsetName;
	sf::Vector2f offsetManual;
	sf::Vector2f offsetSkillPoint;
	sf::Vector2f offsetSkillPoint2;
	sf::Vector2f offsetStar;
	sf::Vector2f offsetStarbyStar;
	sf::Vector2f offsetSkillGroup;
	std::string fontId;

	std::vector<sf::Sprite> upArrows;
	std::vector<sf::Sprite> downArrows;
	std::string texIdArrow;
	sf::Vector2f offsetUpArrow;
	sf::Vector2f offsetDownArrow;
	sf::Vector2i textureRectArrow;

	std::vector<std::vector<sf::Sprite>> stars;
	std::string texIdStar;
	sf::Vector2i textureRectStar;

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
	void ReadSkillData();
	void ChangeSkillManual(int index, bool up);
	void SkillUpDown(int index, bool up);
};
