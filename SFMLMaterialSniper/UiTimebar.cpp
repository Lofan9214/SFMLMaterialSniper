#include "stdafx.h"
#include "UiTimebar.h"

UiTimebar::UiTimebar(const std::string& iName)
	:GameObject(iName)
{
}

void UiTimebar::setPosition(const sf::Vector2f& iPos)
{
	GameObject::setPosition(iPos);
	shpRect.setPosition(vPosition);
}

void UiTimebar::setOrigin(Origins iOrigin)
{
	if (iOrigin < Origins::Custom)
	{
		eOrigin = iOrigin;
		vOrigin = Utilities::setOrigin(shpRect, eOrigin);
	}
}

void UiTimebar::setOrigin(const sf::Vector2f& iOrigin)
{
	eOrigin = Origins::Custom;
	vOrigin = iOrigin;
	shpRect.setOrigin(vOrigin);
}

void UiTimebar::setScale(const sf::Vector2f& iScale)
{
	GameObject::setScale(iScale);
	shpRect.setScale(vScale);
}

void UiTimebar::reset()
{
	setValue(1.f);
}

void UiTimebar::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
	window.draw(shpRect);
}

void UiTimebar::setValue(float iValue)
{
	iValue = Utilities::clamp(iValue, 0.f, 1.f);

	vCurrentSize.x = vMaxSize.x * iValue;
	shpRect.setSize(vCurrentSize);
	setOrigin(eOrigin);
}

void UiTimebar::setTimebar(const sf::Vector2f iSize, const sf::Color& iColor)
{
	vCurrentSize = vMaxSize = iSize;
	shpRect.setFillColor(iColor);
	setValue(1.f);
}
