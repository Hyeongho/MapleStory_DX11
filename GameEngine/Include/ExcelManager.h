#pragma once

#include "GameInfo.h"

class CExcelManager
{
private:
	std::unordered_map<std::string, class CExcel*> m_mapData;

public:
	bool Init();
	
	bool LoadExcel(libxl::Book** Book, const std::string& Name, const TCHAR* FileName, const std::string& PathName = DATA_PATH);
	bool LoadExcelFullPath(const std::string& Name, const TCHAR* FullPath);

	bool SaveExcel(libxl::Book** Book, const std::string& Name, const TCHAR* FileName, const std::string& PathName = DATA_PATH);
	bool SaveExcelFullPath(const std::string& Name, const TCHAR* FullPath);

	class CExcel* FindExcel(const std::string& Name);
	void ReleaseExcel(const std::string& Name);

	DECLARE_SINGLE(CExcelManager)
};

