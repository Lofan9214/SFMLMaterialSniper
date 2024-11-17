#pragma once

class GlassShard : public GameObject
{
protected:

	std::string texId = "graphics/targets/glassshard.png";
	sf::Sprite body;
	sf::Vector2f  speed;
	sf::FloatRect bounds;
	
	int index;

	std::function<void(GlassShard*)> returnThis;

public:
	GlassShard(const std::string& name = "");
	~GlassShard() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetType(int idx);

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void Start(const sf::Vector3f& startpos);
};