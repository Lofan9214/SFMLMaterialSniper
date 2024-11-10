#include "stdafx.h"
#include "UiScore.h"

UiScore::UiScore(const std::string& iFontId, const std::string& iName)
	:TextGo(iFontId, iName)
{
}

void UiScore::reset()
{
	TextGo::reset();
	setScore(0);
}

void UiScore::setScore(int iScore)
{
	dScore = iScore;
	textObj.setString(strFormat + std::to_string(dScore));
}
