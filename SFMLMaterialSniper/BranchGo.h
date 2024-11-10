#pragma once
#include "SpriteGo.h"
class BranchGo :
    public SpriteGo
{
protected:
    Sides eSide = Sides::None;

    BranchGo(const BranchGo&) = delete;
    BranchGo& operator=(const BranchGo&) = delete;

public:
    BranchGo(const std::string& iTexId, const std::string& iName = "");
    virtual ~BranchGo() = default;

    void reset() override;

    void setSide(Sides iSide);
    Sides getSide() { return eSide; }

};

