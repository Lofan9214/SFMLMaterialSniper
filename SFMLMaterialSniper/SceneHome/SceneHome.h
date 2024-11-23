#pragma once

class UiBullet;
class UiSkill;
class UiStage;
class ButtonRound;

class SceneHome : public Scene
{
protected:

	SpriteGo background;
	UiBullet* uiBullet;
	UiSkill* uiSkill;
	UiStage* uiStage;
	ButtonRound* btnGameStart;

public:
	SceneHome();
	virtual ~SceneHome() = default;

	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

