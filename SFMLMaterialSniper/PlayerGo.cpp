#include "stdafx.h"
#include "PlayerGo.h"
#include "SceneDev1.h"

PlayerGo::PlayerGo(const std::string& iName)
	:GameObject(iName)
{
}

void PlayerGo::setSide(Sides iSide)
{
	eSide = iSide;
	sf::Vector2f vNewPos = vPosition + vPlayerLocalPos[(int)eSide];

	setFlipX(!(bool)eSide);

	sprPlayer.setPosition(vNewPos);
	sprAxe.setPosition(vNewPos + vAxeLocalPos);
	sprRip.setPosition(vNewPos + vRipLocalPos);
}

void PlayerGo::onDie()
{
	bAlive = false;
	bChopping = false;
}

void PlayerGo::setPosition(const sf::Vector2f& iPos)
{
	vPosition = iPos;
	setSide(eSide);
}

void PlayerGo::setScale(const sf::Vector2f& iScale)
{
	vScale = iScale;
	sprPlayer.setScale(vScale);
	sprAxe.setScale({ -vScale.x,vScale.y });
	sprRip.setScale({ abs(vScale.x) ,vScale.y });
}

void PlayerGo::setOrigin(Origins iOrigin)
{
	eOrigin = iOrigin;
	if (eOrigin < Origins::Custom)
	{
		vOrigin = Utilities::setOrigin(sprPlayer, eOrigin);
	}
}

void PlayerGo::setOrigin(const sf::Vector2f& iVOrigin)
{
	eOrigin = Origins::Custom;
	vOrigin = iVOrigin;
	sprPlayer.setOrigin(vOrigin);
}

void PlayerGo::setFlipX(bool bFlipX)
{
	GameObject::setFlipX(bFlipX);
	setScale(vScale);
}

void PlayerGo::init()
{
	GameObject::init();
	sprPlayer.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTexIdPlayer));
	setOrigin(Origins::BC);

	sprAxe.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTexIdAxe));
	sprAxe.setOrigin(vAxeOrigin);

	sprRip.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTexIdRip));
	Utilities::setOrigin(sprRip, Origins::BC);
}

void PlayerGo::release()
{
}

void PlayerGo::reset()
{
	bAlive = true;
	bChopping = false;

	sprPlayer.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTexIdPlayer));
	sprAxe.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTexIdAxe));
	sprRip.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTexIdRip));

	setSide(Sides::Right);
}

void PlayerGo::update(float dt)
{
	if (ptrSceneDev1 == nullptr || ptrSceneDev1->getStatus() != SceneDev1::Status::InGame)
	{
		return;
	}

	if (InputMgr::isKeyDown(sf::Keyboard::Left))
	{
		setSide(Sides::Left);
		ptrSceneDev1->OnChop(Sides::Left);
		bChopping = true;
	}
	if (InputMgr::isKeyDown(sf::Keyboard::Right))
	{
		setSide(Sides::Right);
		ptrSceneDev1->OnChop(Sides::Right);
		bChopping = true;
	}
	if (InputMgr::isKeyUp(sf::Keyboard::Left))
	{
		bChopping = false;
	}
	if (InputMgr::isKeyUp(sf::Keyboard::Right))
	{
		bChopping = false;
	}
}

void PlayerGo::draw(sf::RenderWindow& window)
{
	if (bAlive)
	{
		window.draw(sprPlayer);
		if (bChopping)
		{
			window.draw(sprAxe);
		}
	}
	else
	{
		window.draw(sprRip);
	}
}

void PlayerGo::setScene(SceneDev1* iPtrSceneDev1)
{
	ptrSceneDev1 = iPtrSceneDev1;
}
