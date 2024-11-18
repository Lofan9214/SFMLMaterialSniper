#pragma once
#include "DataTable.h"


struct DataWave
{
	std::string type;
	sf::Vector3f position;
};

struct DataStage
{
	std::string stage = "NULL";
	std::unordered_map<int, std::vector<DataWave>> waves;
};

class StageTable : public DataTable
{
public:
	const static DataStage Undefined;

protected:
	std::unordered_map<std::string, DataStage> table;
	std::string filePath = "tables/stage_table.csv";

public:
	StageTable() : DataTable(Types::Stage) {}
	~StageTable() = default;

	bool Load() override;
	void Release() override;

	const DataStage& Get(const std::string& id);
};