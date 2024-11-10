#pragma once
#include "GameObject.h"
class UiTimebar :
    public GameObject
{
protected:

    sf::RectangleShape shpRect;
    sf::Vector2f vMaxSize;
    sf::Vector2f vCurrentSize;

    UiTimebar(const UiTimebar&) = delete;
    UiTimebar& operator=(const UiTimebar&) = delete;

public:
    UiTimebar(const std::string& iName = "");
    virtual ~UiTimebar() = default;

    void setPosition(const sf::Vector2f& iPos) override;
    void setOrigin(Origins iOrigin) override;
    void setOrigin(const sf::Vector2f& iVOrigin) override;
    void setScale(const sf::Vector2f& iScale) override;

    void reset() override;

    void draw(sf::RenderWindow& window) override;

    float getValue() const { return vCurrentSize.x / vMaxSize.x; }
    void setValue(float iValue);

    void setTimebar(const sf::Vector2f iSize, const sf::Color& iColor);

};

