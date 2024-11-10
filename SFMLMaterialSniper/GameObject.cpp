#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& iName)
	:strName(iName), eOrigin(Origins::TL), vOrigin(0.f, 0.f), vScale(1.f, 1.f)
{
}

void GameObject::init()
{
}

void GameObject::release()
{
}

void GameObject::reset()
{
}

void GameObject::update(float dt)
{
}

void GameObject::draw(sf::RenderWindow& window)
{
}

void GameObject::setOrigin(Origins iOrigin)
{
	eOrigin = iOrigin;
	vOrigin = { 0.f,0.f };
}

void GameObject::setFlipX(bool flipx)
{
	bFlipX = flipx;
	if ((bFlipX && vScale.x > 0) || (!bFlipX && vScale.x < 0))
	{
		vScale.x = -vScale.x;
	}
}

void GameObject::setFlipY(bool flipy)
{
	bFlipY = flipy;
	if ((bFlipY && vScale.y > 0) || (!bFlipY && vScale.y < 0))
	{
		vScale.y = -vScale.y;
	}
}
