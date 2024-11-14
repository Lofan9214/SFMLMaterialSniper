#pragma once
class CircleView
{
protected:
	sf::RenderTexture renderTexture;
	sf::View renderView;
	sf::CircleShape rendermask;
	
	float zoom;
	float maskRadius;

	sf::Vector2f position;
public:

	CircleView(float radius,float zoom);
	virtual ~CircleView() = default;

	virtual void SetCircleRadius(float radius);
	virtual void SetZoom(float zoom);
	
	virtual void SetPosition(const sf::Vector2f& pos);

	virtual void Draw(sf::RenderWindow& window, const std::list<GameObject*>& lstobject);
};

