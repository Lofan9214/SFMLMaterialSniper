#pragma once
class DataTable
{
public:
	enum class Types
	{
		String,
	};

protected:
	Types type;

public:
	DataTable(Types t) : type(t) {}
	virtual ~DataTable() = default;

	virtual bool Load() = 0;
	virtual void Release() = 0;
};

