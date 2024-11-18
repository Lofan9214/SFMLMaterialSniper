#pragma once
class CircleView : public GameObject
{
protected:
	sf::RenderTexture renderTexture;
	sf::View renderView;
	sf::CircleShape rendermask;

	float zoom;
	float maskRadius;

	sf::Vector2f position;
public:

	CircleView(const std::string& name = "");
	virtual ~CircleView() = default;

	void SetCircleRadius(float radius);
	void SetZoom(float zoom);

	void SetPosition(const sf::Vector2f& pos) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderTarget& window) override;
};

