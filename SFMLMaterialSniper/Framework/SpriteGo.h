#pragma once

class SpriteGo : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId;

public:
	SpriteGo(const std::string& texId = "", const std::string& name = "");
	~SpriteGo() = default;

	void SetTextureId(const std::string& id) { textureId = id; }

	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);
	void SetDisplacement(const sf::Vector2f& disp) override;
	void SetColor(const sf::Color& color) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& pos) override;
};

