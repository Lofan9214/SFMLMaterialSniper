#pragma once
class Utilities
{
private:
#pragma region ��������
	
#pragma endregion

	static sf::Vector2f setOrigin(sf::Transformable& obj, Origins iOrigin, const sf::FloatRect& objRect);

public:
#pragma region ������ ����

	static sf::Vector2f setOrigin(sf::Sprite& obj, Origins iOrigin);
	static sf::Vector2f setOrigin(sf::Text& obj, Origins iOrigin);
	static sf::Vector2f setOrigin(sf::Shape& obj, Origins iOrigin);

#pragma endregion

#pragma region ��������

	static std::mt19937 generator;

	static void init();

	static float randFloat(float iMin, float iMax);
	static int randInt(int iMin, int iMax);
	static float rand0to1();
	static sf::Vector2f randOnUnitCircle();
	static sf::Vector2f randInUnitCircle();

#pragma endregion

#pragma region �ﰢ�Լ� ����
	
	const static float PI;

	static float rad2deg(float iRad);
	static float deg2rad(float iDeg);

#pragma endregion

	static float clamp(float iValue, float iMin, float iMax);
};

