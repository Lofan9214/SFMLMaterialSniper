#include "stdafx.h"
#include "SoundObject.h"

SoundObject::SoundObject(const std::string& sbId, const std::string& name)
	:soundBufferId(sbId), name(name)
{
	time = 0.f;
	targetTime = 0.f;
	setEnd = false;
}

void SoundObject::Play(bool isLoop)
{
	sfx.setLoop(isLoop);
	sfx.play();
}

void SoundObject::Play(float targetTime)
{
	this->targetTime = targetTime;
	time = 0.f;
	setEnd = true;
	sfx.setLoop(true);
	sfx.play();
}

void SoundObject::Pause()
{
	if (sfx.getStatus() != sf::SoundSource::Status::Playing)
	{
		sfx.pause();
		return;
	}
	sfx.play();
}

void SoundObject::Stop()
{
	sfx.stop();
}

void SoundObject::init()
{
}

void SoundObject::release()
{
}

void SoundObject::reset()
{
	sfx.setBuffer(ResourceMgr<sf::SoundBuffer>::Instance().Get(soundBufferId));
}

void SoundObject::update(float dt)
{
	if (setEnd)
	{
		time += dt;
		if (time >= targetTime)
		{
			setEnd = false;
			sfx.stop();
		}
	}
}