#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& iTexId, const std::string& name)
	:strTextureId(iTexId), GameObject(name)
{

}

void SpriteGo::setPosition(const sf::Vector2f& iPos)
{
	GameObject::setPosition(iPos);
	sprObj.setPosition(iPos);
}

void SpriteGo::setRotation(const float irad)
{
	fRotation = irad;
	sprObj.setRotation(irad * 180 / Utilities::PI);
}

void SpriteGo::setOrigin(Origins preset)
{
	if (preset < Origins::Custom)
	{
		eOrigin = preset;
		vOrigin = Utilities::setOrigin(sprObj, preset);
	}
}

void SpriteGo::setOrigin(const sf::Vector2f& neworigin)
{
	eOrigin = Origins::Custom;
	sprObj.setOrigin(neworigin);
}

void SpriteGo::setFlipX(bool flipX)
{
	GameObject::setFlipX(flipX);
	sprObj.setScale(vScale);
}

void SpriteGo::setFlipY(bool flipY)
{
	GameObject::setFlipX(flipY);
	sprObj.setScale(vScale);
}

void SpriteGo::reset()
{
	sprObj.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTextureId));
	sprObj.setScale(vScale);
	setOrigin(eOrigin);
}

void SpriteGo::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
	window.draw(sprObj);
}

void SpriteGo::drawrect(sf::RenderWindow& window)
{
	sf::RectangleShape shprec;
	auto sprrect = sprObj.getLocalBounds();
	shprec.setPosition(sprrect.getPosition());
	shprec.setSize(sprrect.getSize());

	window.draw(shprec);
}
