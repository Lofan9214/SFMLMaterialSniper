#pragma once
#include "SpriteGo.h"
class EffectLog :
    public SpriteGo
{
protected:

    sf::Vector2f vGravity = { 0.f,1000.f };
    sf::Vector2f vVelocity;

    float fDuration = 3.f;
    float fTimer = 0.f;

    EffectLog(const EffectLog&) = delete;
    EffectLog& operator=(const EffectLog&) = delete;

public:
    EffectLog(const std::string& iTexId, const std::string& iName = "");
    virtual ~EffectLog();

    void update(float dt) override;

    void fire(const sf::Vector2f& iPosition, const sf::Vector2f& iVelocity);

};

