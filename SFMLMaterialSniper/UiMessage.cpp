#include "stdafx.h"
#include "UiMessage.h"

UiMessage::UiMessage(const std::string& fontId, const std::string& name)
	:TextGo(fontId, name)
{
	sortingLayer = SortingLayers::UI;
}

void UiMessage::Init()
{
	SetOrigin(Origins::MC);
	SetFillColor(sf::Color::Red);
	SetTextString("GAME OVER!");
}

void UiMessage::Reset()
{
	TextGo::Reset();
	active = false;
}
