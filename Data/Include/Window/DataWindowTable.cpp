#include "DataWindowTable.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUIManager.h"
#include "Engine.h"
#include "PathManager.h"
#include "../DataManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"

CDataWindowTable::CDataWindowTable()
{
}

CDataWindowTable::~CDataWindowTable()
{
}

void CDataWindowTable::AddSheetList(const char* Name)
{
	m_SheetListWidget->AddItem(Name);
}

bool CDataWindowTable::Init()
{
	CIMGUIWindow::Init();

	m_SheetListWidget = AddWidget<CIMGUIListBox>("SheetList", 300.f, 500.f);

	m_SheetListWidget->SetHideName(true);
	m_SheetListWidget->SetPageItemCount(15);
	m_SheetListWidget->SetSelectCallback(this, &CDataWindowTable::SelectSheet);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectListWidget = AddWidget<CIMGUIListBox>("ObjectList", 300.f, 500.f);

	m_ObjectListWidget->SetHideName(true);
	m_ObjectListWidget->SetPageItemCount(15);
	m_ObjectListWidget->SetSelectCallback(this, &CDataWindowTable::SelectObject);

	return true;
}

void CDataWindowTable::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CDataWindowTable::SelectSheet(int Index, const char* Item)
{
	class CDataWindow* DataWindow = (CDataWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("DataWindow");

	if (!DataWindow)
	{
		return;
	}

	/*if (!m_mapPrevSheet.empty())
	{
		if (m_SheetListWidget->GetSelect())
		{
			m_SheetListWidget->SetSelect(false);
			m_SheetListWidget->SetSelectIndex(-1);
		}
	}*/

	m_mapSheet = DataWindow->GetSheet();

	if (m_mapSheet.empty())
	{
		return;
	}

	auto iter = m_mapSheet.find(Item);

	if (iter == m_mapSheet.end())
	{
		return;
	}

	std::vector<std::string> vecData = iter->second;

	m_ObjectListWidget->Clear();

	size_t Size = vecData.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_ObjectListWidget->AddItem(vecData[i]);
	}

	m_mapPrevSheet = m_mapSheet;
}

void CDataWindowTable::SelectObject(int Index, const char* Item)
{
	class CDataWindow* DataWindow = (CDataWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("DataWindow");

	if (!DataWindow)
	{
		return;
	}

	if (!m_SheetListWidget->GetSelect())
	{
		return;
	}

	m_DataInfo = DataWindow->FindData(Item);

	if (!m_DataInfo)
	{
		return;
	}

	DataWindow->SetDataInfo(m_DataInfo);

	m_PrevDataInfo = m_DataInfo;
}
