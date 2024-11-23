#include "stdafx.h"
#include "BulletTable.h"
#include <io.h>
#include "Includes/rapidcsv.h"

const DataBullet BulletTable::Undefined;

bool BulletTable::Load()
{
	Release();

	if (_access(filePath.c_str(), 0) == -1)
	{
		return false;
	}
	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

	try
	{
		for (int i = 0; i < doc.GetRowCount(); ++i)
		{
			auto row = doc.GetRow<std::string>(i);
			auto find = table.find(row[0]);
			if (find == table.end())
			{
				DataBullet dataBullet;
				dataBullet.name = row[0];
				dataBullet.weight = std::stof(row[1]);
				dataBullet.diameter = std::stof(row[2]);
				dataBullet.muzzleSpeed = std::stof(row[3]);
				table.insert({ row[0],dataBullet });
			}
		}
	}
	catch (std::ios::failure a)
	{
		return false;
	}
	if (table.size() == 0)
	{
		table.insert({ Undefined.name,Undefined });
		return false;
	}
	return true;
}

void BulletTable::Release()
{
	table.clear();
}

const DataBullet& BulletTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end() || id == "default")
	{
		return Undefined;
	}
	return find->second;
}

const DataBullet& BulletTable::Change(bool up)
{
	std::string id = SAVEDATA_MGR.Get().selectedBullet;
	auto find = table.find(id);
	if (find == table.end() || id == "default")
	{
		SAVEDATA_MGR.Get().selectedBullet = Undefined.name;
		return Undefined;
	}
	if (up)
	{
		if (++find == table.end())
		{
			find = table.begin();
		}
	}
	else
	{
		if (find == table.begin())
		{
			find = table.end();
		}
		--find;
	}
	SAVEDATA_MGR.Get().selectedBullet = find->first;
	return find->second;
}
