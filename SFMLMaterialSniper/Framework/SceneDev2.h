#pragma once
#include "Scene.h"
class SceneDev2 : public Scene
{
protected:
    sf::VertexArray va;
    sf::Vector3f bulletpos;
    sf::Vector3f bulletvel;
    sf::Vector3f bulletacc;
    sf::CircleShape bullet;
    sf::Vector3f startpos;
    std::vector<sf::Text> vecText;
    bool fired = false;
    float firetimer = 0.f;
   
public:
    SceneDev2();
    ~SceneDev2() = default;
    void Init() override;
    void Enter() override;
    void Exit() override;

    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

