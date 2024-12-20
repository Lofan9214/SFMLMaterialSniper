#include "stdafx.h"
#include "Utils.h"

std::mt19937 Utils::generator;
const float Utils::PI = acosf(-1.f);

void Utils::Init()
{
	std::random_device rd;
	generator.seed(rd());
}

int Utils::RandomRange(int min, int max)
{
	if (min > max)
	{
		int tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_int_distribution<int> dist(min, max);
	return dist(generator);
}

float Utils::RandomRange(float min, float max)
{
	if (min > max)
	{
		float tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_real_distribution<float> dist(min, max);
	return dist(generator);
}

float Utils::RandomValue()
{
	return RandomRange(0.f, 1.f);
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	float angle = RandomRange(0.f, 2.f * PI);
	return sf::Vector2f(std::cosf(angle), std::sinf(angle));
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

sf::Color Utils::RandomColor(bool opaque)
{
	return sf::Color(
		RandomRange(0, 255),
		RandomRange(0, 255),
		RandomRange(0, 255),
		opaque ? 255 : RandomRange(0, 255)
	);
}

float Utils::Clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

float Utils::Clamp01(float value)
{
	return Clamp(value, 0.f, 1.f);
}

float Utils::Lerp(float min, float max, float t, bool clamp)
{
	if (clamp)
	{
		t = Clamp01(t);
	}
	return min + (max - min) * t;
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp)
{
	if (clamp)
	{
		t = Clamp01(t);
	}

	return min + (max - min) * t;
}

sf::Color Utils::Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp)
{
	if (clamp)
	{
		t = Clamp01(t);
	}

	return sf::Color(
		Lerp(min.r, max.r, t, clamp),
		Lerp(min.g, max.g, t, clamp),
		Lerp(min.b, max.b, t, clamp),
		Lerp(min.a, max.a, t, clamp)
	);
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
	return sqrtf(SqrMagnitude(vec));
}

float Utils::SqrMagnitude(const sf::Vector3f& vec)
{
	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

float Utils::Magnitude(const sf::Vector3f& vec)
{
	return sqrtf(SqrMagnitude(vec));
}

void Utils::Normalize(sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag != 0)
	{
		vec /= mag;
	}
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag == 0)
	{
		return vec;
	}
	return vec / mag;
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p2 - p1);
}

float Utils::RadianToDegree(float radian)
{
	return radian * 180.f / PI;
}

float Utils::DegreeToRadian(float degree)
{
	return degree * PI / 180.f;
}

float Utils::AngleRadian(const sf::Vector2f& vec)
{
	return atan2f(vec.y, vec.x);
}

float Utils::Angle(const sf::Vector2f& vec)
{
	return RadianToDegree(AngleRadian(vec));
}

float Utils::Dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

sf::Vector2f Utils::ElementProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return { a.x * b.x,a.y * b.y };
}

bool Utils::ExpandAndContains(const sf::FloatRect& rect, const sf::Vector2f& point,float expansion)
{
	sf::FloatRect value = rect;
	value.top -= expansion;
	value.left -= expansion;
	value.width += expansion * 2.f;
	value.height += expansion * 2.f;
	
	return value.contains(point);
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect& rect)
{
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;
	obj.setOrigin(newOrigin);
	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins preset)
{
	return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins preset)
{
	return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
{
	return SetOrigin(obj, preset, obj.getLocalBounds());
}

bool Utils::CheckCollision(const sf::Sprite& spriteA, const sf::Sprite& spriteB)
{
	auto pointsA = GetSpritePoints(spriteA);
	auto pointsB = GetSpritePoints(spriteB);
	return PolygonsIntersect(pointsA, spriteA.getTransform(), pointsB, spriteB.getTransform());
}

bool Utils::CheckCollision(const HitBox& boxA, const HitBox& boxB)
{
	return CheckCollision(boxA.rect, boxB.rect);
}

bool Utils::CheckCollision(const sf::RectangleShape& shapeA, const sf::RectangleShape& shapeB)
{
	auto pointsA = GetShapePoints(shapeA);
	auto pointsB = GetShapePoints(shapeB);
	return PolygonsIntersect(pointsA, shapeA.getTransform(), pointsB, shapeB.getTransform());
}

bool Utils::PointInTransformBounds(const sf::Transformable& transformable, const sf::FloatRect& localBounds, const sf::Vector2f& point)
{
	sf::Transform inverse = transformable.getInverseTransform();
	sf::Vector2f localPoint = inverse.transformPoint(point);
	return localBounds.contains(localPoint);
}

std::vector<sf::Vector2f> Utils::GetShapePoints(const sf::RectangleShape& shape)
{
	sf::FloatRect localBounds = shape.getLocalBounds();
	return GetRectanglePointsFromBounds(localBounds);
}

std::vector<sf::Vector2f> Utils::GetSpritePoints(const sf::Sprite& sprite)
{
	sf::FloatRect localBounds = sprite.getLocalBounds();
	return GetRectanglePointsFromBounds(localBounds);
}

std::vector<sf::Vector2f> Utils::GetRectanglePointsFromBounds(const sf::FloatRect& localBounds)
{
	std::vector<sf::Vector2f> points(4);
	points[0] = sf::Vector2f(localBounds.left, localBounds.top);
	points[1] = sf::Vector2f(localBounds.left + localBounds.width, localBounds.top);
	points[2] = sf::Vector2f(localBounds.left + localBounds.width, localBounds.top + localBounds.height);
	points[3] = sf::Vector2f(localBounds.left, localBounds.top + localBounds.height);
	return points;
}

bool Utils::PolygonsIntersect(const std::vector<sf::Vector2f>& polygonA, const sf::Transform& transformA, const std::vector<sf::Vector2f>& polygonB, const sf::Transform& transformB)
{
	std::vector<sf::Vector2f> axes;
	int countA = polygonA.size();
	for (int i = 0; i < countA; ++i)
	{
		sf::Vector2f p1 = transformA.transformPoint(polygonA[i]);
		sf::Vector2f p2 = transformA.transformPoint(polygonA[(i + 1) % countA]);
		sf::Vector2f edge = p2 - p1;
		sf::Vector2f normal(-edge.y, edge.x);
		axes.push_back(Utils::GetNormal(normal));
	}

	int countB = polygonB.size();
	for (int i = 0; i < countB; ++i)
	{
		sf::Vector2f p1 = transformB.transformPoint(polygonB[i]);
		sf::Vector2f p2 = transformB.transformPoint(polygonB[(i + 1) % countB]);
		sf::Vector2f edge = p2 - p1;
		sf::Vector2f normal(-edge.y, edge.x);
		axes.push_back(Utils::GetNormal(normal));
	}

	for (const auto& axis : axes)
	{
		float minA = std::numeric_limits<float>::max();
		float maxA = std::numeric_limits<float>::lowest();
		for (const auto& point : polygonA)
		{
			sf::Vector2f transformedPoint = transformA.transformPoint(point);
			float projection = Dot(axis, transformedPoint);
			minA = std::min(minA, projection);
			maxA = std::max(maxA, projection);
		}

		float minB = std::numeric_limits<float>::max();
		float maxB = std::numeric_limits<float>::lowest();
		for (const auto& point : polygonB)
		{
			sf::Vector2f transformedPoint = transformB.transformPoint(point);
			float projection = Dot(axis, transformedPoint);
			minB = std::min(minB, projection);
			maxB = std::max(maxB, projection);
		}

		if (maxA < minB || maxB < minA)
		{
			return false;
		}
	}
	return true;
}
