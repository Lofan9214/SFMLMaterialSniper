#include "stdafx.h"
#include "Animator.h"

void Animator::BindFunction(GameObject* obj)
{
	FlipX = [obj](bool flipX) {obj->SetFlipX(flipX); };
	SetOrigin = [obj]() {obj->SetOrigin(); };
	SetColor = [obj](const sf::Color& color) {obj->SetColor(color); };
	SetOffset = [obj](const sf::Vector2f& disp) {obj->SetOffset(disp); };
	SetScale = [obj](const sf::Vector2f& scale) { obj->SetAnimationScale(scale); };
	SetRotation = [obj](float rotation) {obj->SetRotation(rotation); };
}

void Animator::AddEvent(const std::string& id, int frame, const std::function<void()>& action)
{
	auto it = events.find({ id,frame });
	if (it != events.end())
	{
		if (action)
		{
			it->second.push_back(action);
		}
		return;
	}
	events.insert({ { id,frame }, {action} });
}

void Animator::ClearEvent(const std::string& id, int frame)
{
	auto it = events.find({ id,frame });
	if (it != events.end())
	{
		it->second.clear();
		return;
	}
}

void Animator::Update(float dt)
{
	if (!isPlaying)
	{
		return;
	}
	frameTimer += dt * std::fabs(speed);
	if (frameTimer < frameDuration)
	{
		return;
	}
	frameTimer = 0.f;

	currentFrame += speed < 0.f ? -1 : 1;
	if (currentFrame == endFrame)
	{
		if (!playQueue.empty())
		{
			std::string clipid = playQueue.front();
			Play(clipid, false);
			playQueue.pop();
			return;
		}

		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = std::abs(endFrame) - 1;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = totalFrame - std::abs(endFrame);
			break;
		}
	}

	SetFrame(currentClip->frames[currentFrame]);

	auto find = events.find({ currentClip->id,currentFrame });
	if (find != events.end())
	{
		for (auto& ev : (*find).second)
		{
			ev();
		}
	}
}

void Animator::Play(const std::string& clipPath, bool clearqueue)
{
	Play(&ANIMATIONCLIP_MGR.Get(clipPath), clearqueue);
}

void Animator::Play(AnimationClip* clip, bool clearqueue)
{
	if (clearqueue)
	{
		while (!playQueue.empty())
		{
			playQueue.pop();
		}
	}
	isPlaying = true;

	currentClip = clip;
	totalFrame = currentClip->frames.size();
	endFrame = this->speed > 0.f ? totalFrame : -1;
	currentFrame = this->speed > 0.f ? 0 : totalFrame - 1;

	frameDuration = 1.f / currentClip->fps;

	frameTimer = 0.f;

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::PlayQueue(const std::string& clipPath)
{
	playQueue.push(clipPath);
}

void Animator::Stop()
{
	isPlaying = false;
	currentFrame = std::abs(endFrame) - 1;
	frameTimer = 0.f;
	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Pause()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	sprite->setTexture(TEXTURE_MGR.Get(frame.texId));
	sprite->setTextureRect(frame.texCoord);
	if (FlipX)
	{
		FlipX(frame.flipX);
	}
	if (SetOrigin)
	{
		SetOrigin();
	}
	if (SetScale)
	{
		SetScale(frame.scale);
	}
	if (SetColor)
	{
		SetColor(frame.color);
	}
	if (SetOffset)
	{
		SetOffset(frame.offset);
	}
	if (frame.rotation != -1 && SetRotation)
	{
		SetRotation(frame.rotation);
	}
}

void Animator::SetFPS(int fps)
{
	currentClip->fps = std::abs(fps);
	frameDuration = 1.f / currentClip->fps;
}
