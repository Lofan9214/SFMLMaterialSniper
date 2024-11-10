#pragma once
#include "SpriteGo.h"
class CloudGo :
    public SpriteGo
{
protected:
	sf::Vector2f vRangeSpeed;
	sf::Vector2f vRangeScale;
	sf::Vector2f vSpeed;
	sf::Vector2f vBounds;
	float fDirection = 0.f;

	CloudGo(const CloudGo&) = delete;
	CloudGo& operator=(const CloudGo&) = delete;

public:
	CloudGo(const std::string& texId, const std::string& name = "");
	virtual ~CloudGo() = default;

	void setRangeSpeed(const sf::Vector2f& iRngSpeed) { vRangeSpeed = iRngSpeed; }
	void setRangeScale(const sf::Vector2f& iRngScale) { vRangeScale = iRngScale; }
	void setSpeed(const sf::Vector2f& iSpeed) { vSpeed = iSpeed; }
	void setBounds(const sf::Vector2f& iBounds) { vBounds = iBounds; }

	void reset() override;
	void update(float dt) override;
};

