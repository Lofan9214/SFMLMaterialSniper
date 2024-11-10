#pragma once
class DebugBox
{
protected:
	sf::RectangleShape shape;
	bool isVisible;

public:
	DebugBox();
	virtual ~DebugBox() = default;

	void SetBounds(const sf::FloatRect& bounds);
	void SetVisible(bool v) { isVisible = v; }
	bool IsVisible() const { return isVisible; }

	void Draw(sf::RenderWindow& window);

	void SetOutlineColor(const sf::Color& color) { shape.setOutlineColor(color); }
};

