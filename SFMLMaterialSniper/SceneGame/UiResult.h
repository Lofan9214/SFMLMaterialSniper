#pragma once

class TextGo;
class ButtonRound;

class UiResult : public GameObject
{
protected:

	sf::RectangleShape titleBackground;
	sf::RectangleShape resultBackground;

	TextGo* txtTitle;
	TextGo* txtResult;

	ButtonRound* btnRetry;
	ButtonRound* btnGohome;

	std::string fontId = "fonts/malgun.ttf";
	std::string buttonTexId = "graphics/ui/uiroundbutton.png";

	float resetTime;

public:
	UiResult(const std::string& name = "");
	~UiResult() = default;

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

	void ShowResult();
};
