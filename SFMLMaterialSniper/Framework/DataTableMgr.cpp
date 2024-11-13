#include "stdafx.h"
#include "DataTable.h"
#include "StringTable.h"
#include "DataTableMgr.h"

DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();
	tables.insert({ DataTable::Types::String, new StringTable() });

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