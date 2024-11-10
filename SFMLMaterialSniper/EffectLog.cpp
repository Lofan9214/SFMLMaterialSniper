#include "stdafx.h"
#include "EffectLog.h"

EffectLog::EffectLog(const std::string& iTexId, const std::string& iName)
	:SpriteGo(iTexId, iName)
{
}

EffectLog::~EffectLog()
{
}

void EffectLog::update(float dt)
{
	fTimer += dt;
	if (fTimer > fDuration)
	{
		bActive = false;
		return;
	}
	vVelocity += vGravity * dt;
	setPosition(vPosition + vVelocity * dt);
}

void EffectLog::fire(const sf::Vector2f& iPosition, const sf::Vector2f& iVelocity)
{
	bActive = true;
	vVelocity = iVelocity;
	vPosition = iPosition;
	fTimer = 0.f;
}
