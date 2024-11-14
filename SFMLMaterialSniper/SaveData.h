#pragma once

struct SaveDataV1;
typedef SaveDataV1 SaveDataVC;

namespace sf
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(sf::Vector2f, x, y)
}

struct SaveData
{
	int version = 0;
	virtual SaveData* VersionUp() = 0;
};

struct SaveDataV1 : public SaveData
{
	SaveDataV1() { version = 1; }

	int scopeSize = 0;
	int stablility = 0;
	int control = 0;
	int reload = 0;
	int magazine = 0;

	SaveData* VersionUp() override;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV1, scopeSize, stablility, control, reload, magazine)
};

