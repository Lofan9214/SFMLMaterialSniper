#pragma once

struct SaveDataV1;
struct SaveDataV2;
typedef SaveDataV2 SaveDataVC;

struct SkillData
{
	int scopeSize = 0;
	int stablility = 0;
	int control = 0;
	int reload = 0;
	int magazine = 0;
	int skillPoint = 20;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SkillData, scopeSize, stablility, control, reload, magazine, skillPoint)
};

struct SaveData
{
	int version = 0;
	virtual SaveData* VersionUp() = 0;
};

struct SaveDataV1 : public SaveData
{
	SaveDataV1() { version = 1; }

	SkillData skillData;

	SaveData* VersionUp() override;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV1,version, skillData)
};

struct SaveDataV2 : public SaveData
{
	SaveDataV2() { version = 2; }

	SkillData skillData;
	std::string selectedBullet;

	SaveData* VersionUp() override;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV2, version, skillData, selectedBullet)
};
