#include "stdafx.h"
#include "Utilities.h"

std::mt19937 Utilities::generator;
const float Utilities::PI = acosf(-1);

sf::Vector2f Utilities::setOrigin(sf::Transformable& obj, Origins iOrigin, const sf::FloatRect& objRect)
{
	sf::Vector2f newOrigin;

	newOrigin.x = objRect.left + objRect.width * ((int)iOrigin % 3) * 0.5f;
	newOrigin.y = objRect.top + objRect.height * ((int)iOrigin / 3) * 0.5f;

	obj.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utilities::setOrigin(sf::Sprite& obj, Origins iOrigin)
{
	return setOrigin(obj, iOrigin, obj.getLocalBounds());
}

sf::Vector2f Utilities::setOrigin(sf::Text& obj, Origins iOrigin)
{
	return setOrigin(obj, iOrigin, obj.getLocalBounds());
}

sf::Vector2f Utilities::setOrigin(sf::Shape& obj, Origins iOrigin)
{
	return setOrigin(obj, iOrigin, obj.getLocalBounds());
}

void Utilities::init()
{
	std::random_device rd;
	generator.seed(rd());
}

float Utilities::randFloat(float iMin, float iMax)
{
	std::uniform_real_distribution<> dist(iMin, iMax);
	return dist(generator);
}

int Utilities::randInt(int iMin, int iMax)
{
	std::uniform_int_distribution<> dist(iMin, iMax);
	return dist(generator);
}

float Utilities::rand0to1()
{
	std::uniform_real_distribution<> dist(0.f, 1.f);
	return dist(generator);
}

sf::Vector2f Utilities::randOnUnitCircle()
{
	float rad = randFloat(0.f, PI * 2.f);
	return sf::Vector2f(std::cosf(rad), std::sinf(rad));
}

sf::Vector2f Utilities::randInUnitCircle()
{
	return randOnUnitCircle() * rand0to1();
}

float Utilities::rad2deg(float iRad)
{
	return iRad * 180.f / Utilities::PI;
}

float Utilities::deg2rad(float iDeg)
{
	return iDeg / 180.f * Utilities::PI;
}

float Utilities::clamp(float iValue, float iMin, float iMax)
{
	if (iValue < iMin)
	{
		return iMin;
	}
	if (iValue > iMax)
	{
		return iMax;
	}

	return iValue;
}
