#pragma once

class WindController : public GameObject
{
protected:

	enum class Status
	{
		Normal,
		Beep1,
		Beep2,
		Beep3,
		End,
	};

	Status status;

	GameDefine::SceneStatus sceneStatus;

	sf::Sprite body;
	std::string texId = "graphics/ui/uiwindchange.png";

	float timer;
	const float duration = 10.f;
	int difficulty;

	std::function<void(int)> windChanged;

	void SetStatus(Status status);

public:
	WindController(const std::string& name = "");
	~WindController() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void SetSceneStatus(GameDefine::SceneStatus status) { sceneStatus = status; }
	void SetDifficulty(int diff);
};
