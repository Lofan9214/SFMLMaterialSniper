#pragma once

#include "TextGo.h"
class WindCone;

class UiHud : public GameObject
{
public:
	enum class ReloadStatus
	{
		Ready,
		MagazineEjecting,
		MagazineInserted,
	};
	enum class BoltStatus
	{
		Ready,
		Fired,
		BoltPulling,
	};

protected:

	sf::Sprite uiBar;
	std::string uiBarTexId = "graphics/ui/uibar.png";
	sf::Sprite uiBarback;
	std::string uiBarbackTexId = "graphics/ui/uibarback.png";

	int ammo;
	BoltStatus boltStatus;
	ReloadStatus reloadStatus;
	float boltTimer;
	float boltDuration;
	float ammodisplacement;
	std::vector<sf::Sprite> uiBullets;
	std::vector<sf::Vector2f> uiBulletDefaultPos;
	sf::Vector2f uiBulletVelocity;
	std::string uiBulletTexId = "graphics/ui/uibullet.png";

	const sf::Vector2f bulletStartPos = { 70.f, 60.f };
	const float bulletOffset = 31.5f;

	sf::VertexArray uiBreath;
	const sf::Vector2f breathMaxSize = { 390.f,50.f };
	const sf::Vector2f breathStartPos = { 460.f,102.f };
	
	WindCone* windCone;
	sf::Sprite uiWindBack;
	std::string uiWindBackTexId = "graphics/ui/uiwindback.png";
	TextGo textWind;

public:
	UiHud(const std::string& name = "");
	~UiHud() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void SetWind(int wind);
	void SetAmmo(int ammo);
	void SetBreath(float breath);
	void SetBoltStatus(BoltStatus status);
	void SetReloadStatus(ReloadStatus status);

	void OnLocalize(Languages lang) override;
};
