#include "stdafx.h"
#include "BranchGo.h"

BranchGo::BranchGo(const std::string& iTexId, const std::string& iName)
	:SpriteGo(iTexId, iName)
{
}

void BranchGo::reset()
{
	SpriteGo::reset();
	setSide(Sides::Rand);
}

void BranchGo::setSide(Sides iSide)
{
	eSide = iSide;
	switch (eSide)
	{
	case Sides::Left:
		bActive = true;
		setFlipX(true);
		break;
	case Sides::Right:
		bActive = true;
		setFlipX(false);
		break;
	case Sides::Rand:
		setSide((Sides)Utilities::randInt((int)Sides::Left, (int)Sides::None));
		break;
	default:
		bActive = false;
		break;
	}

}
