#pragma once

#include "DataWindow.h"
#include "IMGUIWindow.h"

class CDataWindowTable :
    public CIMGUIWindow
{
public:
    CDataWindowTable();
    virtual ~CDataWindowTable();

private:
    class CIMGUIListBox* m_SheetListWidget;
    class CIMGUIListBox* m_ObjectListWidget;
    libxl::Sheet* m_SelectSheet;
    libxl::Sheet* m_PrevObject;

private:
	std::unordered_map<std::string, std::vector<std::string>> m_mapSheet;
	std::unordered_map<std::string, std::vector<std::string>> m_mapPrevSheet;

	DataInfo* m_DataInfo;
	DataInfo* m_PrevDataInfo;

public:
	class CIMGUIListBox* GetSheetList() const
	{
		return m_SheetListWidget;
	}

	class CIMGUIListBox* GetObjectList() const
	{
		return m_ObjectListWidget;
	}

	libxl::Sheet* GetSelectSheet() const
	{
		return m_SelectSheet;
	}

public:
	void AddSheetList(const char* Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
	void SelectSheet(int Index, const char* Item);
	void SelectObject(int Index, const char* Item);
};

