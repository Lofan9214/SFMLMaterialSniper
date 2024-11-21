#pragma once

class ButtonRound : public GameObject
{
protected:

	sf::Sprite buttonBackground;
	std::string buttonTexId = "graphics/ui/uiroundbutton.png";
	sf::Vector2i textureRect;

	sf::Text buttonText;
	std::string buttonFontId = "fonts/malgun.ttf";

	std::function<void()> Clicked;

public:
	ButtonRound(const std::string& name = "");
	~ButtonRound() = default;

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

	void SetString(const std::string& text);
	void SetString(const std::wstring& text);
	void SetClicked(const std::function<void()>& event);
};
