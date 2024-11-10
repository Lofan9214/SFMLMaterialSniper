#include "stdafx.h"

GameObject::GameObject(const std::string& name)
	: name(name), originPreset(Origins::TL), rotation(0.f), scale({ 1.f,1.f }), origin({ 0.f,0.f })
{
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::SetFlipX(bool flipx)
{
	bFlipX = flipx;
	if ((bFlipX && scale.x > 0)
		|| (!bFlipX && scale.x < 0))
	{
		scale.x = -scale.x;
	}
}

void GameObject::SetFlipY(bool flipy)
{
	bFlipY = flipy;
	if ((bFlipY && scale.y > 0)
		|| (!bFlipY && scale.y < 0))
	{
		scale.y = -scale.y;
	}
}
