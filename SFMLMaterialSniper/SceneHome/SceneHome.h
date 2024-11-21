#pragma once

class SceneHome : public Scene
{
protected:

public:
	SceneHome();
	virtual ~SceneHome() = default;

	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

