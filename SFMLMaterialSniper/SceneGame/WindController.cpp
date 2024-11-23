#include "stdafx.h"
#include "WindController.h"
#include "SceneGame.h"

WindController::WindController(const std::string& name)
	: GameObject(name)
{
}

void WindController::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void WindController::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void WindController::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void WindController::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void WindController::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void WindController::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 450;
}

void WindController::Release()
{
}

void WindController::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::BC);

	windChanged = nullptr;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene != nullptr)
	{
		windChanged = [scene](int wind) {scene->SetWind(wind);};
	}
	SetScale({ 0.5f,0.5f });
	active = false;
}

void WindController::Update(float dt)
{
	if (sceneStatus == GameDefine::SceneStatus::Result
		|| sceneStatus == GameDefine::SceneStatus::Awake)
	{
		return;
	}

	timer += dt;
	switch (status)
	{
	case WindController::Status::Normal:
		if (timer > 7.775f)
			SetStatus(Status::Beep1);
		break;
	case WindController::Status::Beep1:
		if (timer > 8.475f)
			SetStatus(Status::Beep2);
		break;
	case WindController::Status::Beep2:
		if (timer > 9.175f)
			SetStatus(Status::Beep3);
		break;
	case WindController::Status::Beep3:
		if (timer > 9.875f)
			SetStatus(Status::End);
		break;
	case WindController::Status::End:
		if (timer > 10.f)
			SetStatus(Status::Normal);
		break;
	default:
		timer = 0.f;
		SetStatus(Status::Normal);
		break;
	}
}

void WindController::Draw(sf::RenderTarget& window)
{
	if (status != Status::Normal
		&& status != Status::End)
	{
		window.draw(body);
	}
}

void WindController::SetStatus(Status status)
{
	Status prev = this->status;
	this->status = status;
	sf::Vector2f size = FRAMEWORK.GetDefaultSize();

	switch (this->status)
	{
	case WindController::Status::Normal:
		timer = 0.f;
		if(prev == Status::End)
		SOUND_MGR.PlaySfx("sounds/ui/windchange.mp3");
		break;
	case WindController::Status::Beep1:
		SetPosition({ 1395.f, size.y - 225.f });
		SOUND_MGR.PlaySfx("sounds/ui/windbeep.mp3");
		break;
	case WindController::Status::Beep2:
		SetPosition({ 1395.f, size.y - 175.f });
		SOUND_MGR.PlaySfx("sounds/ui/windbeep.mp3");
		break;
	case WindController::Status::Beep3:
		SetPosition({ 1395.f, size.y - 125.f });
		SOUND_MGR.PlaySfx("sounds/ui/windbeep.mp3");
		break;
	case WindController::Status::End:
		if (windChanged)
		{
			windChanged(Utils::RandomRange(-difficulty * 8, difficulty * 8));
		}
		SOUND_MGR.PlaySfx("sounds/ui/windchange.mp3");
		break;
	}
}

void WindController::SetDifficulty(int diff)
{
	difficulty = diff;
	SetStatus(Status::Normal);
	if (difficulty == 0)
	{
		active = false;
	}
	else
	{
		active = true;
		timer = 5.7f;
	}
}
