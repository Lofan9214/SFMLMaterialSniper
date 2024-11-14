#pragma once

#include "SaveData.h"

class SaveDataMgr : public Singleton<SaveDataMgr>
{
	friend Singleton<SaveDataMgr>;

private:
	SaveDataMgr() = default;
	~SaveDataMgr() = default;

	std::string savePath = "save.json";

public:
	void Save(const SaveDataVC& saveData);
	SaveDataVC Load();

};

#define SAVEDATA_MGR (SaveDataMgr::Instance())