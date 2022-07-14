#pragma once

#include "Ref.h"

class CExcel : 
	public CRef
{
	friend class CExcelManager;

protected:
	CExcel();
	virtual ~CExcel();

public:
	bool LoadExcel(libxl::Book** Book, const std::string& Name, const TCHAR* FileName, const std::string& PathName = DATA_PATH);
	bool LoadExcelFullPath(const std::string& Name, const TCHAR* FullPath);

	bool SaveExcel(libxl::Book** Book, const std::string& Name, const TCHAR* FileName, const std::string& PathName = DATA_PATH);
	bool SaveExcelFullPath(const std::string& Name, const TCHAR* FullPath);
};

