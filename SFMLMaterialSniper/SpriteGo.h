#pragma once
class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprObj;
	std::string strTextureId;

	SpriteGo(const SpriteGo&) = delete;
	SpriteGo& operator=(const SpriteGo&) = delete;

public:
	~SpriteGo() = default;

	SpriteGo(const std::string& iTexId, const std::string& iName = "");
	void setResourceId(const std::string& iResId) { strTextureId = iResId; }

	void setPosition(const sf::Vector2f& iPos) override;
	void setRotation(const float iRad);

	void setOrigin(Origins iOrigin) override;
	void setOrigin(const sf::Vector2f& iVOrigin) override;

	void setFlipX(bool iFlipX) override;
	void setFlipY(bool iFlipY) override;

	void reset() override;
	void draw(sf::RenderWindow& window) override;
	void drawrect(sf::RenderWindow& window);
};

