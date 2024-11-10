#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& iFontId, const std::string& iName)
	:strFontId(iFontId), GameObject(iName)
{
}

void TextGo::reset()
{
	textObj.setFont(ResourceMgr<sf::Font>::Instance().get(strFontId));
	setOrigin(eOrigin);
}

void TextGo::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
	window.draw(textObj);
}

void TextGo::setOrigin(Origins iOrigin)
{
	if (iOrigin < Origins::Custom)
	{
		eOrigin = iOrigin;
		vOrigin = Utilities::setOrigin(textObj, iOrigin);
	}
}

void TextGo::setOrigin(const sf::Vector2f& iVOrigin)
{
	eOrigin = Origins::Custom;
	vOrigin = iVOrigin;
	textObj.setOrigin(vOrigin);
}

void TextGo::setPosition(const sf::Vector2f& iPos)
{
	GameObject::setPosition(iPos);
	textObj.setPosition(vPosition);
}

void TextGo::setString(const std::string& strChange)
{
	textObj.setString(strChange);
	setOrigin(eOrigin);
}

void TextGo::setCharSize(unsigned int iSize)
{
	textObj.setCharacterSize(iSize);
	setOrigin(eOrigin);
}

void TextGo::setTextColor(const sf::Color& iColor)
{
	textObj.setFillColor(iColor);
}
