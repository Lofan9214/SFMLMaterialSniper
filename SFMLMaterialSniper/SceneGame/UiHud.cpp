#include "stdafx.h"
#include "UiHud.h"
#include "UiWindIcon.h"
#include "UiHelpMessage.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	uiBar.setPosition(position);
	uiBarback.setPosition(position);
}

void UiHud::SetRotation(float angle)
{
	rotation = angle;
	uiBar.setRotation(rotation);
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	scale = s;
	uiBar.setScale(scale);
}

void UiHud::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(uiBar, originPreset);
		uiBarback.setOrigin({ origin.x + 10.f,origin.y - 25.f });
	}
}

void UiHud::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	uiBar.setOrigin(origin);
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = (int)GameDefine::UiSortingOrders::UiHud;

	uiBullets.resize(12);
	uiBulletDefaultPos.resize(12);

	boltDuration = 0.5f;
	boltTimer = boltDuration * 8.f;
	ammoOffset = 15.f;

	windCone = new WindIcon("windcone");
	windCone->Init();

	windArrow = new WindIcon("windIcon");
	windArrow->Init();

	reload = new HelpMessage("reload");
	reload->Init();

	space = new HelpMessage("space");
	space->Init();

	fire = new HelpMessage("fire");
	fire->Init();
}

void UiHud::Release()
{
	uiBullets.clear();
	windCone->Release();
	delete windCone;
	windArrow->Release();
	delete windArrow;
	reload->Release();
	delete reload;
	space->Release();
	delete space;
	fire->Release();
	delete fire;
}

void UiHud::Reset()
{
	uiBar.setTexture(TEXTURE_MGR.Get(uiBarTexId));
	uiBarback.setTexture(TEXTURE_MGR.Get(uiBarbackTexId));
	uiWindBack.setTexture(TEXTURE_MGR.Get(uiWindBackTexId));
	textWind.SetFont(FONT_MGR.Get("fonts/malgun.ttf"));
	textWindName.SetFont(FONT_MGR.Get("fonts/malgun.ttf"));

	boltStatus = BoltStatus::Ready;
	reloadStatus = ReloadStatus::Ready;

	float textSize = 50.f;
	sf::Vector2f size = FRAMEWORK.GetDefaultSize();

	textWind.SetCharSize(textSize);
	textWind.SetColor({ 50,50,50 });
	textWind.SetOutline(sf::Color::White, 2.f);
	textWind.SetOrigin(Origins::MC);

	textWindName.SetCharSize(30.f);
	textWindName.SetString("Wind", true);
	textWindName.SetColor(sf::Color::White);
	textWindName.SetOrigin(Origins::TC);
	textWindName.SetPosition({ 1165.f, size.y - 55.f });

	textWind.SetPosition({ 1395.f,size.y - 75.f });

	SetOrigin(Origins::BL);
	SetPosition({ 0.f,size.y + 12.f });

	for (int i = 0; i < uiBullets.size(); ++i)
	{
		uiBullets[i].setTexture(TEXTURE_MGR.Get(uiBulletTexId));
		uiBullets[i].setScale({ 0.575f,0.575f });
		Utils::SetOrigin(uiBullets[i], Origins::BC);
		uiBulletDefaultPos[i].x = bulletStartPos.x + i * bulletOffset;
		uiBulletDefaultPos[i].y = position.y - bulletStartPos.y;
		uiBullets[i].setPosition(uiBulletDefaultPos[i]);
	}
	float ratio = 1600.f / 2276.f;
	uiBar.setScale(ratio, ratio);
	uiBarback.setScale(ratio, ratio);

	uiBreath.resize(4);
	uiBreath.setPrimitiveType(sf::PrimitiveType::TrianglesStrip);
	uiBreath[0].position = { breathStartPos.x + breathMaxSize.x,position.y - breathStartPos.y + breathMaxSize.y };
	uiBreath[1].position = { breathStartPos.x + breathMaxSize.x,position.y - breathStartPos.y };
	uiBreath[2].position = { breathStartPos.x, position.y - breathStartPos.y + breathMaxSize.y };
	uiBreath[3].position = { breathStartPos.x, position.y - breathStartPos.y };

	windCone->Reset();
	windCone->SetType(WindIcon::Type::Cone);
	windCone->SetScale({ 2.f, 2.f });
	windCone->SetPosition({ 1165.f, size.y - 55.f });
	windCone->SetOrigin(Origins::MC);

	windArrow->Reset();
	windArrow->SetType(WindIcon::Type::Arrow);
	windArrow->SetScale({ 1.2f, 1.2f });
	windArrow->SetPosition({ 1335.f,size.y - 65.f });
	windArrow->SetOrigin(Origins::MR);
	windArrow->SetActive(false);

	reload->Reset();
	reload->SetPosition(size * 0.5f);
	reload->SetActive(false);

	space->Reset();
	space->SetOrigin(Origins::ML);
	space->SetPosition({ 0.f,size.y * 0.5f });
	space->SetActive(false);

	fire->Reset();
	fire->SetPosition({ size.x * 0.85f,size.y * 0.5f });
	fire->SetActive(false);

	uiWindBack.setScale(2.8f, 2.8f);
	uiWindBack.setPosition(1395.f, size.y - 65.f);
	Utils::SetOrigin(uiWindBack, Origins::MC);
}

void UiHud::LateUpdate(float dt)
{
}

void UiHud::Update(float dt)
{
	windCone->Update(dt);
	reload->Update(dt);
	space->Update(dt);
	fire->Update(dt);
	windArrow->Update(dt);
	switch (boltStatus)
	{
	case UiHud::BoltStatus::BoltPulling:
		for (int i = 0; i < ammo; ++i)
		{
			boltTimer -= dt;
			uiBullets[i].move(dt * ammoOffset / (boltDuration - 0.1f), 0.f);
			if (boltTimer < 0.1f)
			{
				uiBullets[i].setRotation(2.f);
			}
		}
		if (boltTimer < 0.f)
		{
			SetBoltStatus(BoltStatus::Ready);
		}
		break;
	}

	switch (reloadStatus)
	{
	case UiHud::ReloadStatus::MagazineEjecting:
		uiBulletVelocity.y += 10000.f * dt;
		for (int i = 0; i < uiBullets.size(); ++i)
		{
			uiBullets[i].move(uiBulletVelocity * dt);
		}
		break;
	case UiHud::ReloadStatus::MagazineInserted:
		for (int i = 0; i < uiBullets.size(); ++i)
		{
			uiBullets[i].move(uiBulletVelocity * dt);
			uiBullets[i].setColor({ 255,255,255,(sf::Uint8)((400.f + uiBulletDefaultPos[i].x - uiBullets[i].getPosition().x) / 400.f * 255.f) });
		}
		if (uiBullets[0].getPosition().x < uiBulletDefaultPos[0].x)
		{
			SetReloadStatus(ReloadStatus::Ready);
		}
		break;
	}
}

void UiHud::FixedUpdate(float dt)
{
}

void UiHud::Draw(sf::RenderTarget& window)
{
	window.draw(uiBarback);
	for (int i = 0; i < ammo; ++i)
	{
		window.draw(uiBullets[i]);
	}
	window.draw(uiBreath);
	window.draw(uiWindBack);
	textWind.Draw(window);
	window.draw(uiBar);
	windCone->Draw(window);
	textWindName.Draw(window);
	if (reload->IsActive())
	{
		reload->Draw(window);
	}
	if (space->IsActive())
	{
		space->Draw(window);
	}
	if (fire->IsActive())
	{
		fire->Draw(window);
	}
	if (windArrow->IsActive())
	{
		windArrow->Draw(window);
	}
}

void UiHud::SetWind(int wind)
{
	if (wind == 0)
	{
		textWind.SetString("Windless", true);
		textWind.SetColor({ 50,50,50 });
	}
	else
	{
		textWind.SetString(std::to_string(wind));
		textWind.SetColor(sf::Color::Green);

		sf::Vector2f arrpos = windArrow->GetPosition();
		windArrow->SetPosition({ 1395.f + (wind > 0 ? 1.f : -1.f) * 60.f,arrpos.y });
	}
	windCone->SetWindSpeed(wind);
	windArrow->SetWindSpeed(wind);
}

void UiHud::SetAmmo(int ammo)
{
	this->ammo = ammo;
}

void UiHud::SetBreath(float breath)
{
	uiBreath[0].position.x = breathStartPos.x + breathMaxSize.x * breath;
	uiBreath[1].position.x = breathStartPos.x + breathMaxSize.x * breath;

	uiBreath[0].color = { (sf::Uint8)(250 - 120 * breath),(sf::Uint8)(255 * (-breath * (2.f * breath - 2.8f))),(sf::Uint8)(255 * breath) };
	uiBreath[1].color = uiBreath[0].color;
	uiBreath[2].color = uiBreath[0].color - sf::Color(50, 50, 50, 0);
	uiBreath[3].color = uiBreath[2].color;
}

void UiHud::SetBoltStatus(BoltStatus status)
{
	boltStatus = status;
	switch (boltStatus)
	{
	case UiHud::BoltStatus::Ready:
		for (int i = 0; i < uiBullets.size(); ++i)
		{
			uiBullets[i].setRotation(0.f);
			uiBullets[i].setPosition(uiBulletDefaultPos[i]);
		}
		break;
	case UiHud::BoltStatus::Fired:
		for (int i = 0; i < ammo; ++i)
		{
			uiBullets[i].setRotation(-20.f);
			uiBullets[i].move(-ammoOffset * 0.5f, 0.f);
		}
		break;
	case UiHud::BoltStatus::BoltPulling:
		boltTimer = boltDuration;
		for (int i = 0; i < ammo; ++i)
		{
			uiBullets[i].move(-ammoOffset * 0.5f, 0.f);
			uiBullets[i].setRotation(0.f);
		}
		--ammo;
		break;
	}
}

void UiHud::SetReloadStatus(ReloadStatus status)
{
	reloadStatus = status;
	uiBulletVelocity.x = 0.f;
	uiBulletVelocity.y = 0.f;
	switch (reloadStatus)
	{
	case UiHud::ReloadStatus::Ready:
		for (int i = 0; i < uiBullets.size(); ++i)
		{
			uiBullets[i].setColor(sf::Color::White);
			uiBullets[i].setRotation(0.f);
			uiBullets[i].setPosition(uiBulletDefaultPos[i]);
		}
		break;
	case UiHud::ReloadStatus::MagazineEjecting:
		uiBulletVelocity.y = -500.f;
		break;
	case UiHud::ReloadStatus::MagazineInserted:
		uiBulletVelocity.x = -2000.f;
		for (int i = 0; i < uiBullets.size(); ++i)
		{
			uiBullets[i].setColor({ 255,255,255,0 });
			uiBullets[i].setRotation(45.f);
			uiBullets[i].setPosition(uiBulletDefaultPos[i].x + 400.f, uiBulletDefaultPos[i].y);
		}
		break;
	}
}

void UiHud::OnLocalize(Languages lang)
{
	textWind.OnLocalize(lang);
}

void UiHud::SetReloadActive(bool active)
{
	reload->SetActive(active);
}

void UiHud::SetSpaceActive(bool active, float duration)
{
	space->SetActive(active);
	space->StartTimer(duration);
}

void UiHud::SetFireActive(bool active, float duration)
{
	fire->SetActive(active);
	fire->StartTimer(duration);
}

