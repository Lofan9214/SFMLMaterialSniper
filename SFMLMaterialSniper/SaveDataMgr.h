#pragma once

#include "SaveData.h"

class SaveDataMgr : public Singleton<SaveDataMgr>
{
	friend Singleton<SaveDataMgr>;
public:

private:
	SaveDataMgr() = default;
	~SaveDataMgr() = default;

	std::string savePath = "tables/save.json";

	SaveDataVC data;

public:
	void Save();
	SaveDataVC Load();

	SaveDataVC& Get() { return data; }
	SaveDataVC Get() const { return data; }
};

#define SAVEDATA_MGR (SaveDataMgr::Instance())