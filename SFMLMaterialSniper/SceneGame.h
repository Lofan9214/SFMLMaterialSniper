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
public:
	enum class Status
	{
		Awake,
		InGame,
		Interlude,
	};


protected:
	Status currentStatus = Status::Awake;
	
    Bullet* bullet;
    CircleView* scopeview;
	Player* player;

    sf::Vector3f startpos;

	std::list<GlassShard*> glassShards;
	ObjectPool<GlassShard> glassShardPool;

	std::list<Drum*> drums;
	ObjectPool<Drum> drumPool;

	std::list<Bottle*> bottles;
	ObjectPool<Bottle> bottlePool;

	std::list<RoundBoard*> roundboards;
	ObjectPool<RoundBoard> roundboardPool;

    UiHud* uiHud;

    float wind = 0.f;
	
	float interludeTimer = 0.f;

	int verse = 0;

public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status status);
	void UpdateAwake(float dt);
	void UpdateInGame(float dt);
	void UpdateInterlude(float dt);

	GlassShard* TakeGlassShard();
	void ReturnGlassShard(GlassShard* glassShard);

	void ClearTookObject();

	void SpawnDrum(const sf::Vector3f& pos);
	void SpawnBottle(const sf::Vector3f& pos);
	void SpawnRoundBoard(const sf::Vector3f& pos);
};

