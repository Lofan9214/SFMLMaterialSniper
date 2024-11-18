#include "stdafx.h"
#include "StageTable.h"
#include "Includes/rapidcsv.h"

const DataStage StageTable::Undefined;

bool StageTable::Load()
{
	Release();

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

	try
	{
		for (int i = 0;i < doc.GetRowCount();++i)
		{
			auto row = doc.GetRow<std::string>(i);
			auto find = table.find(row[0]);
			DataWave dataWave;
			dataWave.type = row[2];
			dataWave.position = { std::stof(row[3]),std::stof(row[4]),std::stof(row[5]) };
			if (find != table.end())
			{
				auto find2 = find->second.waves.find(std::stoi(row[1]));
				if (find2 != find->second.waves.end())
				{
					find2->second.push_back(dataWave);
				}
				else
				{
					find->second.waves.insert({ std::stoi(row[1]),{dataWave} });
				}
			}
			else
			{
				DataStage dataStage;
				dataStage.stage = row[0];
				dataStage.waves.insert({ std::stoi(row[1]),{dataWave} });
				table.insert({ row[0],dataStage });
			}
		}
	}
	catch (std::ios::failure a)
	{
		return false;
	}
	if (table.size() == 0)
	{
		return false;
	}
	return true;
}

void StageTable::Release()
{
	table.clear();
}

const DataStage& StageTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}
