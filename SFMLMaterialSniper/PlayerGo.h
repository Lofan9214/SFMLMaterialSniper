#pragma once
#include "GameObject.h"

class SceneDev1;

class PlayerGo :
	public GameObject
{
protected:
	sf::Sprite sprPlayer;
	sf::Sprite sprAxe;
	sf::Sprite sprRip;

	std::string strTexIdPlayer = "graphics/player.png";
	std::string strTexIdAxe = "graphics/axe.png";
	std::string strTexIdRip = "graphics/rip.png";

	Sides eSide = Sides::Right;

	sf::Vector2f vPlayerLocalPos[3] = { {-300.f,0.f},{300.f,0.f},{0.f,0.f} };
	sf::Vector2f vAxeLocalPos = { 0.f,-70.f };
	sf::Vector2f vRipLocalPos = { 0.f,0.f };

	sf::Vector2f vAxeOrigin = { -60.f,0.f };

	bool bAlive = true;
	bool bChopping = false;

	SceneDev1* ptrSceneDev1 = nullptr;

	PlayerGo(const PlayerGo&) = delete;
	PlayerGo& operator=(const PlayerGo&) = delete;

public:
	PlayerGo(const std::string& iName = "");
	virtual ~PlayerGo() = default;

	Sides getSide() { return eSide; }
	void setSide(Sides iSide);
	void onDie();

	void setPosition(const sf::Vector2f& iPos) override;
	void setScale(const sf::Vector2f& iScale) override;
	void setOrigin(Origins iOrigin) override;
	void setOrigin(const sf::Vector2f& iVOrigin) override;
	void setFlipX(bool bFlipX) override;

	void init() override;
	void release() override;

	void reset() override;

	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

	void setScene(SceneDev1* iPtrSceneDev1);
};

