#pragma once
#include "SpriteGo.h"
class BeeGo :
	public SpriteGo
{
protected:
	sf::Vector2f vRangeSpeed;
	sf::Vector2f vRangeScale;
	sf::Vector2f vSpeed;
	sf::Vector2f vBounds;
	float fDirection = 0.f;

public:
	BeeGo(const std::string& iTexId, const std::string& iName = "");
	virtual ~BeeGo() = default;

	void setRangeSpeed(const sf::Vector2f& iRngSpeed) { this->vRangeSpeed = iRngSpeed; }
	void setSpeed(const sf::Vector2f& iSpeed) { this->vSpeed = iSpeed; }
	void setBounds(const sf::Vector2f& iBounds) { this->vBounds = iBounds; }
	void setScale(const sf::Vector2f& iScale) { this->vRangeScale = iScale; }

	void reset() override;
	void update(float dt) override;
};

