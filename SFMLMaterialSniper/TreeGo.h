#pragma once
#include "GameObject.h"
#include "BranchGo.h"
#include "EffectLog.h"

class TreeGo :
    public GameObject
{
protected:
    sf::Sprite sprTree;
    std::list<BranchGo*> lstBranch;

    int cntBranch = 6;

    std::string strTreeTexId = "graphics/tree.png";
    std::string strBranchTexId = "graphics/branch.png";

    float offsetYBranch = 150.f;

    ObjectPool<EffectLog> objpoolEffectLog;

    TreeGo(const TreeGo&) = delete;
    TreeGo& operator=(const TreeGo&) = delete;

public:
    TreeGo(const std::string& iName = "");
    virtual ~TreeGo();

    Sides chop(Sides iSide);
    void updateBranchPos();

    void init() override;
    void release() override;

    void reset() override;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    void setPosition(const sf::Vector2f& iPos) override;
};

