#pragma once
#include "DataTable.h"


struct DataWave
{
	std::string type;
	sf::Vector3f position;
	sf::Vector2f velocity;
};

struct DataStage
{
	int stage = 0;
	std::unordered_map<int, std::vector<DataWave>> waves;
};

class StageTable : public DataTable
{
public:
	const static DataStage Undefined;

protected:
	std::unordered_map<int, DataStage> table;
	std::string filePath = "tables/stage_table.csv";

public:
	StageTable() : DataTable(Types::Stage) {}
	~StageTable() = default;

	bool Load() override;
	void Release() override;

	const DataStage& Get(int id);
};