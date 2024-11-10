#include "stdafx.h"
#include "CloudGo.h"

CloudGo::CloudGo(const std::string& iTexId, const std::string& iName)
	:SpriteGo(iTexId,iName),vRangeSpeed(100.f,200.f),vRangeScale(1.f,2.f)
{
}

void CloudGo::reset()
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
	vScale.x = -fDirection * Utilities::randFloat(vRangeScale.x, vRangeScale.y);
	vScale.y = Utilities::randFloat(vRangeScale.x, vRangeScale.y);

	vPosition.x = (vBounds.y - vBounds.x) * (0.5f - fDirection * 0.5f) + vBounds.x;
	vPosition.y = Utilities::randFloat(10.f,300.f);

	setPosition(vPosition);
	SpriteGo::reset();
}

void CloudGo::update(float dt)
{
	setPosition(vPosition + vSpeed * dt);

	if (vPosition.x<vBounds.x || vPosition.x > vBounds.y)
	{
		reset();
	}
}
