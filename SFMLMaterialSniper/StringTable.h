#pragma once
#include "DataTable.h"
class StringTable :
    public DataTable
{
public:
    const static std::wstring Undefined;

protected:
    std::unordered_map<std::string, std::wstring> table;
    std::string filePath = "tables/string_table.csv";

public:
    StringTable() : DataTable(Types::String) {}
    ~StringTable() = default;
    
    bool Load() override;
    void Release() override;
    void OnLocalize();

    const std::wstring& Get(const std::string& id);
};

