#pragma once

class Bullet;
class CircleView;
class Drum;
class RoundBoard;
class Bottle;
class UiHud;
class Player;
class GlassShard;
class Gun;
class BulletShell;
class UiResult;
class ButtonRound;
class WindController;
class ShootMark;

class SceneGame :
	public Scene
{
protected:
	GameDefine::SceneStatus currentStatus = GameDefine::SceneStatus::Awake;

	CircleView* scopeview;
	Player* player;
	Gun* gun;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	std::list<BulletShell*> bulletShells;
	ObjectPool<BulletShell> bulletShellPool;

	std::list<GlassShard*> glassShards;
	ObjectPool<GlassShard> glassShardPool;

	std::list<Drum*> drums;
	ObjectPool<Drum> drumPool;

	std::list<Bottle*> bottles;
	ObjectPool<Bottle> bottlePool;

	std::list<RoundBoard*> roundboards;
	ObjectPool<RoundBoard> roundboardPool;

	UiHud* uiHud;
	UiResult* uiResult;
	WindController* windController;
	std::list<ShootMark*> shootmarks;

	DataStage dataStage;

	float wind = 0.f;

	float interludeTimer = 0.f;

	int remains;
	int stage;
	int difficulty;
	bool day;
	int wave;

	float screenRecoil;
	float screenRecoilTimer;

public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetStatus(GameDefine::SceneStatus status);
	void UpdateAwake(float dt);
	void UpdateInGame(float dt);
	void UpdateInterlude(float dt);
	void UpdateResult(float dt);
	void UpdateScreenRecoil(float dt);

	GlassShard* TakeGlassShard();
	void ReturnGlassShard(GlassShard* glassShard);

	Bullet* TakeBullet();
	const std::list<Bullet*>& GetBulletList() { return bullets; }
	void ReturnBullet(Bullet* bullet);

	BulletShell* TakeBulletShell();
	void ReturnBulletShell(BulletShell* bulletShell);

	void ClearTookObject();

	void ResetScreenRecoilTimer() { screenRecoilTimer = 0.f; }
	void TargetHit() { --remains; }
	void SpawnWave();

	void SpawnDrum(const sf::Vector3f& pos);
	void SpawnBottle(const sf::Vector3f& pos);
	void SpawnRoundBoard(const sf::Vector3f& pos);
	void ReturnDrum(Drum* drum);
	void ReturnBottle(Bottle* bottle);
	void ReturnRoundBoard(RoundBoard* roundboard);

	void SetStage(int stage, int diff, bool day);
	void SetWind(int speed);
};

