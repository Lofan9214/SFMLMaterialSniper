#pragma once
#include "Scene.h"
class SceneDev2 :
    public Scene
{
protected:
    
    SceneDev2(const SceneDev2&) = delete;
    SceneDev2& operator=(const SceneDev2&) = delete;
public:
    SceneDev2();
    virtual ~SceneDev2() = default;

    void init() override;
    void enter() override;
    void exit() override;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};

