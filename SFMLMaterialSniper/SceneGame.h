#pragma once
#include "Scene.h"

class Bullet;
class CircleView;
class Drum;
class RoundBoard;
class Bottle;
class UiHud;
class Player;
class GlassShard;

class SceneGame :
	public Scene
{
protected:
    Bullet* bullet;
    CircleView* scopeview;
    Drum* drum;
    Bottle* bottle;
    RoundBoard* roundBoard;
	Player* player;

    sf::Vector3f startpos;

	std::list<GlassShard*> glassShards;
	ObjectPool<GlassShard> glassShardPool;

    UiHud* uiHud;

    float wind = 0.f;

public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	GlassShard* TakeGlassShard();
	void ReturnGlassShard(GlassShard* glassShard);
};

