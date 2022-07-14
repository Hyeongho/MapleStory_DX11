#include "Excel.h"
#include "PathManager.h"

CExcel::CExcel()
{
}

CExcel::~CExcel()
{
}

bool CExcel::LoadExcel(libxl::Book** Book, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	SetName(Name);

	WCHAR FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(DATA_PATH);

	if (Info)
	{
		lstrcpy(FullPath, Info->Path);
	}

	lstrcat(FullPath, FileName);

	char Ext[_MAX_EXT] = {};
	char FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else
	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	_splitpath_s(FullPathMultibyte, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

	_strupr_s(Ext);

	if (strcmp(Ext, ".xlsx"))
	{
		*Book = xlCreateXMLBook();
	}

	else if (strcmp(Ext, ".xls"))
	{
		*Book = xlCreateBook();
	}

	return (*Book)->load(FullPath);
}

bool CExcel::LoadExcelFullPath(const std::string& Name, const TCHAR* FullPath)
{
	return true;
}

bool CExcel::SaveExcel(libxl::Book** Book, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	WCHAR FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(DATA_PATH);

	if (Info)
	{
		lstrcpy(FullPath, Info->Path);
	}

	lstrcat(FullPath, FileName);

	char Ext[_MAX_EXT] = {};
	char FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else
	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	return (*Book)->save(FullPath);
}

bool CExcel::SaveExcelFullPath(const std::string& Name, const TCHAR* FullPath)
{
	return true;
}
