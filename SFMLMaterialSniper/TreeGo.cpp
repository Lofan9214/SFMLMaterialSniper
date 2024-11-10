#include "stdafx.h"
#include "TreeGo.h"


TreeGo::TreeGo(const std::string& iName)
	:GameObject(iName)
{
}

TreeGo::~TreeGo()
{
	release();
}

Sides TreeGo::chop(Sides iSide)
{
	if (iSide == Sides::Left)
	{
		EffectLog* effect = objpoolEffectLog.take();
		SceneMgr::Instance().getCurrentScene()->addGo(effect);
		effect->setOrigin(Origins::BC);
		effect->fire(vPosition, { 1000.f,-1000.f });
	}
	else if (iSide == Sides::Right)
	{
		EffectLog* effect = objpoolEffectLog.take();
		SceneMgr::Instance().getCurrentScene()->addGo(effect);
		effect->setOrigin(Origins::BC);
		effect->fire(vPosition, { -1000.f,-1000.f });
	}

	BranchGo* temp = lstBranch.front();
	lstBranch.pop_front();

	temp->setSide(Sides::Rand);

	lstBranch.push_back(temp);
	updateBranchPos();

	return lstBranch.front()->getSide();
}

void TreeGo::updateBranchPos()
{
	sf::Vector2f pos = vPosition;
	for (auto branch : lstBranch)
	{
		pos.y -= offsetYBranch;
		branch->setPosition(pos);
	}
}

void TreeGo::init()
{
	release();

	sprTree.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTreeTexId), true);
	Utilities::setOrigin(sprTree, Origins::BC);

	objpoolEffectLog.setResourceId("graphics/log.png");

	sf::Vector2f originBranch;

	originBranch.x = sprTree.getLocalBounds().width * -0.5f;
	sf::Texture& branchtex = ResourceMgr<sf::Texture>::Instance().get(strBranchTexId);
	originBranch.y = branchtex.getSize().y * 0.5f;

	for (int i = 0;i < cntBranch;++i)
	{
		BranchGo* branch = new BranchGo(strBranchTexId, "Branch");
		branch->setOrigin(originBranch);
		branch->init();
		branch->setSide(Sides::Rand);
		lstBranch.push_back(branch);
	}

}

void TreeGo::release()
{
	SceneMgr::Instance().getCurrentScene()->removeGo(objpoolEffectLog.getListUsing());

	for (auto branch : lstBranch)
	{
		branch->release();
		delete branch;
	}
	lstBranch.clear();
}

void TreeGo::reset()
{
	sprTree.setTexture(ResourceMgr<sf::Texture>::Instance().get(strTreeTexId), true);

	for (auto branch : lstBranch)
	{
		branch->reset();
	}
	lstBranch.front()->setSide(Sides::None);

	updateBranchPos();
}

void TreeGo::update(float dt)
{
	for (auto branch : lstBranch)
	{
		if (branch->getActive())
		{
			branch->update(dt);
		}
	}

	SceneMgr::Instance().getCurrentScene()->removeGo(objpoolEffectLog.update(dt));
}

void TreeGo::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
	window.draw(sprTree);

	for (auto branch : lstBranch)
	{
		if (branch->getActive())
		{
			branch->draw(window);
		}
	}
}

void TreeGo::setPosition(const sf::Vector2f& iPos)
{
	GameObject::setPosition(iPos);
	sprTree.setPosition(vPosition);
	updateBranchPos();
}
