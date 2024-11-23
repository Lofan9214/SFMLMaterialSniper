#pragma once
#include "DataTable.h"

struct DataBullet
{
	std::string name = ".300 Winchester";
	float weight = 11.7f;
	float diameter = 7.82f;
	float muzzleSpeed = 973.f;
};

class BulletTable : public DataTable
{
public:
	const static DataBullet Undefined;

protected:
	std::string selectedBullet;
	std::unordered_map<std::string, DataBullet> table;
	std::string filePath = "tables/bullet_table.csv";

public:
	BulletTable() : DataTable(Types::Stage) {}
	~BulletTable() = default;

	bool Load() override;
	void Release() override;

	const DataBullet& Get(const std::string& id); 
	const DataBullet& Change(bool up);
};

