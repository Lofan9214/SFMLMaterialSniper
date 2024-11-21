#include "stdafx.h"
#include <io.h>
#include "SaveDataMgr.h"

void SaveDataMgr::Save()
{
	json saveJson = data;
	std::ofstream saveStream(savePath);

	saveStream << saveJson.dump(4) << std::endl;
	saveStream.close();
}

SaveDataVC SaveDataMgr::Load()
{
	if (_access(savePath.c_str(), 0) == -1)
	{
		data = SaveDataVC();
		return data;
	}

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
	case 2:
	{
		SaveDataV2 v2 = loadJson.get<SaveDataV2>();
		saveData = new SaveDataV2(v2);
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
	data = SaveDataVC(*ptr);
	delete saveData;

	return data;
}