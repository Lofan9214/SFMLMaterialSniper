#pragma once
#include "Scene.h"

class TreeGo;
class PlayerGo;
class TextGo;
class UiScore;
class UiTimebar;

class SceneDev1 :
	public Scene
{
public:
	enum class Status
	{
		Awake,
		InGame,
		GameOver,
		Pause,
	};

protected:
	Status eStatus = Status::Awake;

	TreeGo* ptrTree;
	PlayerGo* ptrPlayer;

	TextGo* txtCenterMessage;
	UiScore* uiScore;
	UiTimebar* uiTimebar;

	int dScore = 0;
	float fGameTime = 0.f;
	float fMaxGameTime = 5.f;

	SceneDev1(const SceneDev1&) = delete;
	SceneDev1& operator=(const SceneDev1&) = delete;
public:
	SceneDev1();
	virtual ~SceneDev1() = default;

	void init() override;
	void enter() override;
	void exit() override;

	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

	void setCenterMessage(const std::string& iMessage);
	void setVisibleCenterMessage(bool iVisible);
	void setScore(int score);

	Status getStatus() const { return eStatus; }
	void setStatus(Status iStatus);
	void updateAwake(float dt);
	void updateInGame(float dt);
	void updateGameOver(float dt);
	void updatePause(float dt);

	void OnChop(Sides side);
};

