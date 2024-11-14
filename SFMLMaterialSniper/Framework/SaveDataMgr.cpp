#include "stdafx.h"
#include "SaveDataMgr.h"

void SaveDataMgr::Save(const SaveDataVC& saveData)
{
	json saveJson = saveData;
	std::ofstream saveStream(savePath);

	saveStream << saveJson.dump(4) << std::endl;
	saveStream.close();
}

SaveDataVC SaveDataMgr::Load()
{
	std::ifstream loadStream(savePath);
	json loadJson = json::parse(loadStream);
	loadStream.close();

	int version = loadJson["version"];
	SaveData* saveData = nullptr;

	switch (version)
	{
	case 1:
	{
		SaveDataV1 v1 = loadJson.get<SaveDataV1>();
		saveData = new SaveDataV1(v1);
		break;
	}
	default:
	{
		SaveDataVC vc = loadJson.get<SaveDataVC>();
		saveData = new SaveDataVC(vc);
		break;
	}
	}

	while (saveData->version < Variables::currentVersion)
	{
		SaveData* oldData = saveData;
		saveData = oldData->VersionUp();
		delete oldData;
	}

	SaveDataVC* ptr = dynamic_cast<SaveDataVC*>(saveData);
	SaveDataVC ret(*ptr);
	delete saveData;

	return ret;
}
