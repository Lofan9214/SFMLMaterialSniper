#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	std::string texId;
	sf::IntRect texCoord;
	bool flipX;
	sf::Vector2f scale;
	sf::Color color;
	sf::Vector2f displacement;
	float rotation;

	AnimationFrame() = default;
};

struct AnimationClip
{
	std::string id;
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop;
	int fps = 30;

	std::vector<AnimationFrame>frames;

	bool loadFromFile(const std::string& filePath);
};
