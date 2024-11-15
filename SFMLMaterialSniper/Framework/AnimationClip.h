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

	AnimationFrame() = default;
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord,bool flipX) : texId(texId), texCoord(texCoord), flipX(flipX){}
};

struct AnimationClip
{
	std::string id;
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop;
	int fps = 30;

	std::vector<AnimationFrame>frames;

	bool loadFromFile(const std::string& filePath);
};
