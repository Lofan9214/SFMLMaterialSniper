#include "stdafx.h"
#include "StringTable.h"
#include "Includes/rapidcsv.h"

const std::wstring StringTable::Undefined = L"NULL";

bool StringTable::Load()
{
	Release();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	std::string strLang = "";
	switch (Variables::currentLang)
	{
	case Languages::Korean:
		strLang = "_Korean";
		break;
	}
	filePath = "tables/string_table" + strLang + ".csv";
	rapidcsv::Document doc;

	//ToDo : 파일 로드 실패시 Try-Catch로 묶었으나 어떻게 처리할 지 생각 필요
	try
	{
		doc.Load(filePath, rapidcsv::LabelParams(0, -1));
	}
	catch(std::ios::failure a)
	{
		return false;
	}

	for (int i = 0;i < doc.GetRowCount();++i)
	{
		std::vector<std::string> strings = doc.GetRow<std::string>(i);
		auto it = table.find(strings[0]);

		table[strings[0]] = converter.from_bytes(strings[1]);
	}
	return true;
}

void StringTable::Release()
{
	table.clear();
}

void StringTable::OnLocalize()
{
	Load();
}

const std::wstring& StringTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}

	return find->second;
}
