#pragma once

class TextGo;

class UiStage : public GameObject
{
protected:
	sf::RectangleShape background;

	TextGo* title;
	TextGo* manual;
	TextGo* difficulty;
	std::string fontId;
	sf::Vector2f offsetTitle;
	sf::Vector2f offsetManual;
	sf::Vector2f offsetDifficulty;

	sf::Sprite upArrow;
	sf::Vector2f offsetUpArrow;
	sf::Sprite downArrow;
	sf::Vector2f offsetDownArrow;
	std::string texId;
	sf::Vector2i textureRect;

public:
	UiStage(const std::string& name = "");
	~UiStage() = default;

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

	void ShowDiff();
};
