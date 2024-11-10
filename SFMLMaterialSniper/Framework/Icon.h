#pragma once


class Icon : public GameObject
{
protected:

	sf::Sprite icon;
	std::string textureId = "graphics/spr_HoloBombIcon.png";
	sf::VertexArray mask;
	sf::Sprite drawnicon;
	sf::RenderTexture texture;
	sf::RenderStates maskRenderState;
	float timer;
	float maxTime;

public:
	Icon(const std::string& name = "");
	~Icon() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SetTime(float time, float delay);
};

