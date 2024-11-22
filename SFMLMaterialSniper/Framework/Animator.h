#pragma once

#include "AnimationClip.h"

struct AnimationEvent
{
	std::string id;
	int frame = 0;

	bool operator==(const AnimationEvent& other) const { return (id == other.id) && (frame == other.frame); }
};

struct AnimationEventHash
{
	std::size_t operator()(const AnimationEvent& ev) const
	{
		std::hash<std::string> stringHash = std::hash<std::string>();
		std::size_t hStr = stringHash(ev.id);
		std::size_t hInt = std::hash<int>()(ev.frame);
		return hStr ^ (hInt << 1);
	}
};

class GameObject;

class Animator
{
protected:
	std::unordered_map<AnimationEvent, std::list<std::function<void()>>, AnimationEventHash> events;
	std::queue<std::string> playQueue;

	AnimationClip* currentClip;
	sf::Sprite* sprite;

	bool isPlaying = false;
	int currentFrame = 0;
	int totalFrame = 0;
	int endFrame = 0;
	float frameDuration = 0.f;
	float frameTimer = 0.f;

	float speed = 1.f;

	std::function<void(bool flipx)> FlipX;
	std::function<void()> SetOrigin;
	std::function<void(const sf::Color&)> SetColor;
	std::function<void(const sf::Vector2f&)> SetScale;
	std::function<void(const sf::Vector2f&)> SetDisplacement;
	std::function<void(float)> SetRotation;

public:
	Animator() = default;
	virtual ~Animator() = default;

	void SetSpeed(float spd)
	{
		speed = spd;
		endFrame = speed > 0.f ? totalFrame : -1;
	}

	void SetSprite(sf::Sprite* spr) { sprite = spr; }
	void BindFunction(GameObject* obj);

	void AddEvent(const std::string& id, int frame, const std::function<void()>& action);
	void ClearEvent() { events.clear(); }
	void ClearEvent(const std::string& id, int frame);

	void Update(float dt);

	bool IsPlaying() const { return isPlaying; }

	void Play(const std::string& clipPath, bool clearqueue = true);
	void Play(AnimationClip* clip, bool clearqueue = true);
	void PlayQueue(const std::string& clipPath);
	void Stop();
	void Pause();

	void SetFrame(const AnimationFrame& frame);

	void SetFPS(int fps);

	const std::string& GetCurrentClipId()
	{
		if (currentClip == nullptr)
		{
			return "NULL";
		}
		return currentClip->id;
	}
};

