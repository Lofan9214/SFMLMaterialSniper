#include "stdafx.h"
#include "BeeGo.h"

BeeGo::BeeGo(const std::string& iTexId, const std::string& iName)
	:SpriteGo(iTexId, iName), vRangeSpeed(300.f, 400.f), vRangeScale(1.f, 2.f)
{
}

void BeeGo::reset()
{
	if (Utilities::randInt(0, 1) == 1)
	{
		fDirection = 1.f;
	}
	else
	{
		fDirection = -1.f;
	}

	vSpeed.x = fDirection * Utilities::randFloat(vRangeSpeed.x, vRangeSpeed.y);
	vSpeed.y = Utilities::randFloat(vRangeSpeed.x, vRangeSpeed.y);
	vScale.x = -fDirection * Utilities::randFloat(vRangeScale.x, vRangeScale.y);
	vScale.y = Utilities::randFloat(vRangeScale.x, vRangeScale.y);

	vPosition.x = (vBounds.y - vBounds.x) * (0.5f - fDirection * 0.5f) + vBounds.x;
	vPosition.y = Utilities::randFloat(500.f, 900.f);

	setPosition(vPosition);
	SpriteGo::reset();
}

void BeeGo::update(float dt)
{
	vPosition.x += vSpeed.x * dt;
	vPosition.y += vSpeed.y * dt * sinf(Framework::Instance().getGameTime() * 3.14f);
	//적분이므로 y 진폭은 vSpeed.y/3.14f

	setPosition(vPosition);

	if (vPosition.x < vBounds.x || vPosition.x > vBounds.y)
	{
		reset();
	}
}
