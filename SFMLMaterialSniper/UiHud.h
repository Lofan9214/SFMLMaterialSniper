#pragma once

#include "TextGo.h"

class TextGo;

class UiHud : public GameObject
{
protected:

	TextGo textWind;
	TextGo textAmmo;
	TextGo textBreath;

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
	void SetBreath(int breath);

	void OnLocalize(Languages lang) override;
};
