#pragma once
#include "Scene.h"

class Bullet;
class CircleView;
class Drum;
class RoundBoard;
class Bottle;

class SceneGame :
	public Scene
{
protected:
    sf::VertexArray va;
    Bullet* bullet;
    CircleView* scopeview;
    Drum* drum;
    Bottle* bottle;
    RoundBoard* roundBoard;

    sf::Vector3f startpos;
    std::vector<sf::Text> vecText;

    sf::Text textMoa;
    sf::Text textWind;

    float wind = 0.f;
    bool fired = false;
    bool firedfront = false;
    float firetimer = 0.f;

public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

