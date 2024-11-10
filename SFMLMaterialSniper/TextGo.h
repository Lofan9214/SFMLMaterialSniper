#pragma once
#include "GameObject.h"
class TextGo :
	public GameObject
{
protected:
	sf::Text textObj;
	std::string strFontId;

	TextGo() = delete;

	TextGo(const TextGo&) = delete;
	TextGo& operator=(const TextGo&) = delete;
public:
	~TextGo() = default;
	TextGo(const std::string& iFontId, const std::string& iName = "");

	void reset() override;
	void draw(sf::RenderWindow& window) override;

	void setOrigin(Origins iOrigin) override;
	void setOrigin(const sf::Vector2f& iVOrigin) override;
	void setPosition(const sf::Vector2f& iPos) override;

	void setString(const std::string& strSet);
	void setCharSize(unsigned int iSize);
	void setTextColor(const sf::Color& iColor);
};

