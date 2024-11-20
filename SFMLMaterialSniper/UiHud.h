#pragma once

#include "TextGo.h"

class TextGo;

class UiHud : public GameObject
{
protected:

	TextGo textWind;

	sf::Sprite uiBar;
	std::string uiBarTexId = "graphics/ui/uibar.png";

	int ammo;
	float fireTimer;
	const float fireDuration = 0.3f;
	std::vector<sf::Sprite> uiBullets;
	std::string uiBulletTexId = "graphics/ui/uibullet.png";

	const sf::Vector2f bulletStartPos = { 71.f, 45.f };
	const float bulletOffset = 31.f;

	sf::VertexArray uiBreath;
	const sf::Vector2f breathMaxSize = { 390.f,50.f };
	const sf::Vector2f breathStartPos = { 460.f,92.f };
	
	sf::Sprite uiWindCone;
	std::string uiWindCone = "graphics/ui/uiWindCone.png";


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
	void Fired();

	void OnLocalize(Languages lang) override;
};
