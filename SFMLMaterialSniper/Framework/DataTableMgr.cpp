#include "stdafx.h"
#include "DataTableMgr.h"

DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();
	tables.insert({ DataTable::Types::String, new StringTable() });
	tables.insert({ DataTable::Types::Stage, new StageTable() });
	tables.insert({ DataTable::Types::Bullet, new BulletTable() });

	for (auto t : tables)
	{
		t.second->Load();
	}
}

void DataTableMgr::Release()
{
	for (auto t : tables)
	{
		t.second->Release();
		delete t.second;
	}
	tables.clear();
}