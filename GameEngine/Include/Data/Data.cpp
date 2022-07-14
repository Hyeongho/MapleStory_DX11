#include "Data.h"
#include "../ExcelManager.h"

CData::CData() : m_Excel(nullptr), m_Sheet(nullptr)
{
}

CData::~CData()
{
	//ReleaseBook();
}

void CData::LoadExcel(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CExcelManager::GetInst()->LoadExcel(&m_Excel ,Name, FileName, PathName);
}

void CData::SaveExcel(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
}

libxl::Book* CData::MakeExcel(const std::string& Name)
{
	size_t Pos = Name.rfind('.');

	std::string str = Name.substr(Pos + 1);

	if (str == "xlsx")
	{
		return xlCreateXMLBook();
	}

	else if (str == "xls")
	{
		return xlCreateBook();
	}

	return nullptr;
}
