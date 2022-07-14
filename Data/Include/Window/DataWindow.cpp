#include "DataWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUIMenuBar.h"
#include "IMGUISeparator.h"
#include "IMGUIModal.h"
#include "Engine.h"
#include "PathManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"
#include "IMGUIManager.h"
#include "DataWindowTable.h"
#include "ExcelManager.h"

CDataWindow::CDataWindow() : m_Data(nullptr)
{
}

CDataWindow::~CDataWindow()
{
	//m_Data->m_Excel->release();

	SAFE_DELETE(m_Data);
}

bool CDataWindow::Init()
{
	CIMGUIWindow::Init();

	m_Data = new CData;

	AddWindowFlag(ImGuiWindowFlags_MenuBar);

	EnableModalPopup();

	SetPopupWindowTitle("DataModal");

	m_MenuBar = AddWidget<CIMGUIMenuBar>("File");

	m_MenuBar->SetSelectCallback(this, &CDataWindow::SelectMenu);

	// Input Name
	CIMGUILabel* Label = AddWidget<CIMGUILabel>("Name", 100.f, 30.f);
	Label->SetColor(0, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_InputName = AddWidget<CIMGUITextInput>("InputName", 100.f, 100.f);
	m_InputName->SetHideName(true);
	m_InputName->AddFlag(ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputName->SetTextType(ImGuiText_Type::String);
	m_InputName->SetCallback(this, &CDataWindow::CallBackName);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextName = AddWidget<CIMGUIText>("Name", 100.f, 100.f);
	m_TextName->SetText("Name");
	m_TextName->SetTextType(Text_Type::Multibyte);
	m_TextName->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(400.f);

	m_TypeCombo = AddWidget<CIMGUIComboBox>("ObjectCombo", 150.f, 30.f);

	m_TypeCombo->SetHideName(true);
	m_TypeCombo->AddItem("Player");
	m_TypeCombo->AddItem("Monster");

	CIMGUISeparator* Separator = AddWidget<CIMGUISeparator>("Separator");

	// Input HP;
	Label = AddWidget<CIMGUILabel>("HP", 100.f, 30.f);
	Label->SetColor(0, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputHP = AddWidget<CIMGUITextInput>("InputHP");
	m_InputHP->SetHideName(true);
	m_InputHP->SetTextType(ImGuiText_Type::Int);
	m_InputHP->SetCallback(this, &CDataWindow::CallBackHP);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextHP = AddWidget<CIMGUIText>("HP", 300.f);
	std::string str = std::to_string(m_DataInfo.HP);
	m_TextHP->SetText(str.c_str());
	m_TextHP->SetColor(255, 255, 255);

	Separator = AddWidget<CIMGUISeparator>("Separator");

	// Input MP
	Label = AddWidget<CIMGUILabel>("MP", 100.f, 30.f);
	Label->SetColor(0, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputMP = AddWidget<CIMGUITextInput>("InputMP");
	m_InputMP->SetHideName(true);
	m_InputMP->SetTextType(ImGuiText_Type::Int);
	m_InputMP->SetCallback(this, &CDataWindow::CallBackMP);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextMP = AddWidget<CIMGUIText>("MP", 300.f);
	str = std::to_string(m_DataInfo.MP);
	m_TextMP->SetText(str.c_str());
	m_TextMP->SetColor(255, 255, 255);

	Separator = AddWidget<CIMGUISeparator>("Separator");

	// Input Exp
	Label = AddWidget<CIMGUILabel>("Exp", 100.f, 30.f);
	Label->SetColor(0, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputExp = AddWidget<CIMGUITextInput>("InputExp");
	m_InputExp->SetHideName(true);
	m_InputExp->SetTextType(ImGuiText_Type::Int);
	m_InputExp->SetCallback(this, &CDataWindow::CallBackExp);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextExp = AddWidget<CIMGUIText>("Exp", 300.f);
	str = std::to_string(m_DataInfo.Exp);
	m_TextExp->SetText(str.c_str());
	m_TextExp->SetColor(255, 255, 255);

	Separator = AddWidget<CIMGUISeparator>("Separator");

	// Input Level
	Label = AddWidget<CIMGUILabel>("Level", 100.f, 30.f);
	Label->SetColor(0, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputLevel = AddWidget<CIMGUITextInput>("InputLevel");
	m_InputLevel->SetHideName(true);
	m_InputLevel->SetTextType(ImGuiText_Type::Int);
	m_InputLevel->SetCallback(this, &CDataWindow::CallBackLevel);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextLevel = AddWidget<CIMGUIText>("Level", 300.f);
	str = std::to_string(m_DataInfo.Level);
	m_TextLevel->SetText(str.c_str());
	m_TextLevel->SetColor(255, 255, 255);

	Separator = AddWidget<CIMGUISeparator>("Separator");

	// Input Attack
	Label = AddWidget<CIMGUILabel>("Attack", 100.f, 30.f);
	Label->SetColor(0, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputAttack = AddWidget<CIMGUITextInput>("InputAttack");
	m_InputAttack->SetHideName(true);
	m_InputAttack->SetTextType(ImGuiText_Type::Int);
	m_InputAttack->SetCallback(this, &CDataWindow::CallBackAttack);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextAttack = AddWidget<CIMGUIText>("Attack", 300.f);
	str = std::to_string(m_DataInfo.Attack);
	m_TextAttack->SetText(str.c_str());
	m_TextAttack->SetColor(255, 255, 255);

	Separator = AddWidget<CIMGUISeparator>("Separator");

	// Input Armor
	Label = AddWidget<CIMGUILabel>("Armor", 100.f, 30.f);
	Label->SetColor(0, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputArmor = AddWidget<CIMGUITextInput>("InputArmor");
	m_InputArmor->SetHideName(true);
	m_InputArmor->SetTextType(ImGuiText_Type::Int);
	m_InputArmor->SetCallback(this, &CDataWindow::CallBackArmor);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextArmor = AddWidget<CIMGUIText>("Armor", 300.f);
	str = std::to_string(m_DataInfo.Armor);
	m_TextArmor->SetText(str.c_str());
	m_TextArmor->SetColor(255, 255, 255);

	Separator = AddWidget<CIMGUISeparator>("Separator");

	// Input Monster_Type

	// AddData Button
	m_AddData = AddWidget<CIMGUIButton>("Add", 100.f, 30.f);
	m_AddData->SetClickCallback(this, &CDataWindow::AddCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	// DeleteData Button
	m_DeleteData = AddWidget<CIMGUIButton>("Delete", 100.f, 30.f);
	m_DeleteData->SetClickCallback(this, &CDataWindow::DeleteCallback);

	// DataSave Button
	m_DataSaveButton = AddWidget<CIMGUIButton>("DataSave", 100.f, 30.f);
	m_DataSaveButton->SetClickCallback(this, &CDataWindow::SaveDataCallback);

	// Modal
	m_Text = AddPopupWidget<CIMGUIText>("Text");
	m_Text->SetHideName(true);

	Line = AddPopupWidget<CIMGUISameLine>("Line");

	m_InputText = AddPopupWidget<CIMGUITextInput>("InputText");
	m_InputText->SetHideName(true);

	m_SaveButton = AddPopupWidget<CIMGUIButton>("Save");
	m_SaveButton->SetClickCallback(this, &CDataWindow::SaveCallback);

	Line = AddPopupWidget<CIMGUISameLine>("Line");

	m_LoadButton = AddPopupWidget<CIMGUIButton>("Load");
	m_LoadButton->SetClickCallback(this, &CDataWindow::LoadCallback);

	return true;
}

void CDataWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CDataWindow::SetDataInfo(DataInfo* Data)
{
	m_DataInfo.Name = Data->Name;
	m_DataInfo.HP = Data->HP;
	m_DataInfo.MP = Data->MP;
	m_DataInfo.Attack = Data->Attack;
	m_DataInfo.Armor = Data->Armor;
	m_DataInfo.Exp = Data->Exp;
	m_DataInfo.Level = Data->Level;

	m_TextName->SetText(m_DataInfo.Name.c_str());

	std::string str = std::to_string(m_DataInfo.HP);
	m_TextHP->SetText(str.c_str());

	str = std::to_string(m_DataInfo.MP);
	m_TextMP->SetText(str.c_str());

	str = std::to_string(m_DataInfo.Exp);
	m_TextExp->SetText(str.c_str());

	str = std::to_string(m_DataInfo.Level);
	m_TextLevel->SetText(str.c_str());

	str = std::to_string(m_DataInfo.Attack);
	m_TextAttack->SetText(str.c_str());

	str = std::to_string(m_DataInfo.Armor);
	m_TextArmor->SetText(str.c_str());
}

std::vector<std::string> CDataWindow::FindDataVector(std::string Name)
{
	auto iter = m_mapSheet.find(Name);

	if (iter == m_mapSheet.end())
	{
		return m_mapSheet.end()->second;
	}

	return iter->second;
}

DataInfo* CDataWindow::FindData(std::string Name)
{
	auto iter = m_mapData.find(Name);

	if (iter == m_mapData.end())
	{
		return nullptr;
	}

	return &(iter->second);
}

void CDataWindow::CallBackName()
{
	m_DataInfo.Name = m_InputName->GetTextUTF8();

	m_TextName->SetText(m_InputName->GetTextMultibyte());
}

void CDataWindow::CallBackHP()
{
	m_DataInfo.HP = m_InputHP->GetValueInt();

	std::string str = std::to_string(m_DataInfo.HP);

	m_TextHP->SetText(str.c_str());
}

void CDataWindow::CallBackMP()
{
	m_DataInfo.MP = m_InputMP->GetValueInt();

	std::string str = std::to_string(m_DataInfo.MP);

	m_TextMP->SetText(str.c_str());
}

void CDataWindow::CallBackExp()
{
	m_DataInfo.Exp = m_InputExp->GetValueInt();

	std::string str = std::to_string(m_DataInfo.Exp);

	m_TextExp->SetText(str.c_str());
}

void CDataWindow::CallBackLevel()
{
	m_DataInfo.Level = m_InputLevel->GetValueInt();

	std::string str = std::to_string(m_DataInfo.Level);

	m_TextLevel->SetText(str.c_str());
}

void CDataWindow::CallBackAttack()
{
	m_DataInfo.Attack = m_InputAttack->GetValueInt();

	std::string str = std::to_string(m_DataInfo.Attack);

	m_TextAttack->SetText(str.c_str());
}

void CDataWindow::CallBackArmor()
{
	m_DataInfo.Armor = m_InputArmor->GetValueInt();

	std::string str = std::to_string(m_DataInfo.Armor);

	m_TextArmor->SetText(str.c_str());
}

void CDataWindow::AddCallback()
{
	CDataWindowTable* DataWindowTable = (CDataWindowTable*)CIMGUIManager::GetInst()->FindIMGUIWindow("DataWindowTable");

	if (!DataWindowTable)
	{
		return;
	}

	CIMGUIListBox* SheetListBox = DataWindowTable->GetSheetList();

	if (!SheetListBox)
	{
		return;
	}

	if (!SheetListBox->GetSelect())
	{
		return;
	}

	CIMGUIListBox* ObjectListBox = DataWindowTable->GetObjectList();

	if (!ObjectListBox)
	{
		return;
	}

	auto iter = m_mapSheet.find(SheetListBox->GetSelectItem());

	if (iter == m_mapSheet.end())
	{
		return;
	}

	iter->second.push_back(m_DataInfo.Name);

	m_mapData.insert(std::make_pair(m_DataInfo.Name, m_DataInfo));

	ObjectListBox->AddItem(m_DataInfo.Name);
}

void CDataWindow::DeleteCallback()
{
}

void CDataWindow::SaveDataCallback()
{
	CDataWindowTable* DataWindowTable = (CDataWindowTable*)CIMGUIManager::GetInst()->FindIMGUIWindow("DataWindowTable");

	if (!DataWindowTable)
	{
		return;
	}

	CIMGUIListBox* SheetListBox = DataWindowTable->GetSheetList();

	if (!SheetListBox)
	{
		return;
	}

	if (!SheetListBox->GetSelect())
	{
		return;
	}

	CIMGUIListBox* ObjectListBox = DataWindowTable->GetObjectList();

	if (!ObjectListBox)
	{
		return;
	}

	{
		auto iter = m_mapSheet.find(SheetListBox->GetSelectItem());

		if (iter == m_mapSheet.end())
		{
			return;
		}
	}	

	{
		auto iter = m_mapData.find(ObjectListBox->GetSelectItem());

		if (iter == m_mapData.end())
		{
			return;
		}

		iter->second = m_DataInfo;
	}
}

void CDataWindow::SelectMenu(int Index, std::string Label)
{
	OpenModal();
}

void CDataWindow::SaveCallback()
{
	//m_Data->SaveExcel(m_InputText->GetTextMultibyte());

	libxl::Book* book = m_Data->MakeExcel(m_InputText->GetTextMultibyte());

	if (!book)
	{
		ClosePopup();

		return;
	}

	CDataWindowTable* DataWindowTable = (CDataWindowTable*)CIMGUIManager::GetInst()->FindIMGUIWindow("DataWindowTable");

	if (!DataWindowTable)
	{
		ClosePopup();

		return;
	}

	auto iter = m_mapSheet.begin();
	auto iterEnd = m_mapSheet.end();

	for (; iter != iterEnd; iter++)
	{
		const wchar_t* SheetName = CEngine::GetInst()->ConverCtoWC(iter->first.c_str());

		libxl::Sheet* sheet = book->addSheet(SheetName);

		auto vecIter = iter->second.begin();
		auto vecIterEnd = iter->second.end();

		int FirstCol = sheet->firstCol() + 1;

		sheet->writeStr(FirstCol, 0, L"Name");
		sheet->writeStr(FirstCol, 1, L"HP");
		sheet->writeStr(FirstCol, 2, L"MP");
		sheet->writeStr(FirstCol, 3, L"Attack");
		sheet->writeStr(FirstCol, 4, L"Armor");
		sheet->writeStr(FirstCol, 5, L"Level");
		sheet->writeStr(FirstCol, 6, L"Exp");

		FirstCol++;

		for ( ; vecIter != vecIterEnd; vecIter++)
		{
			auto DataIter = m_mapData.find(*vecIter);

			if (DataIter == m_mapData.end())
			{
				continue;
			}

			DataInfo Data = DataIter->second;

			const wchar_t* ObjName = CEngine::GetInst()->ConverCtoWC(Data.Name.c_str());

			sheet->writeStr(FirstCol, 0, ObjName);
			sheet->writeNum(FirstCol, 1, Data.HP);
			sheet->writeNum(FirstCol, 2, Data.MP);
			sheet->writeNum(FirstCol, 3, Data.Attack);
			sheet->writeNum(FirstCol, 4, Data.Armor);
			sheet->writeNum(FirstCol, 5, Data.Level);
			sheet->writeNum(FirstCol, 6, Data.Exp);

			FirstCol++;
		}
	}

	CExcelManager::GetInst()->SaveExcel(&book, m_InputText->GetTextMultibyte(), m_InputText->GetText());

	book->release();

	ClosePopup();
}

void CDataWindow::LoadCallback()
{
	m_Data->LoadExcel(m_InputText->GetTextMultibyte(), m_InputText->GetText());

	libxl::Book* book = m_Data->GetBook();

	if (!book)
	{
		ClosePopup();

		return;
	}

	int size = book->sheetCount();

	CDataWindowTable* DataWindowTable = (CDataWindowTable*)CIMGUIManager::GetInst()->FindIMGUIWindow("DataWindowTable");

	if (!DataWindowTable)
	{
		ClosePopup();

		return;
	}

	for (int i = 0; i < size; i++)
	{
		libxl::Sheet* sheet = book->getSheet(i);

		if (sheet)
		{
			CIMGUIListBox* SheetListBox = DataWindowTable->GetSheetList();

			const wchar_t* wSheetName = book->getSheetName(i);

			char* SheetName = CEngine::GetInst()->ConvertWCtoC(book->getSheetName(i));

			std::string str = SheetName;

			SheetListBox->AddItem(SheetName);

			int FirstCol = sheet->firstCol() + 2;
			int LastCol = sheet->lastCol() + 2;

			CIMGUIListBox* ObjListBox = DataWindowTable->GetObjectList();

			for (int j = FirstCol; j < LastCol; j++)
			{
				if (sheet->readStr(j, 0))
				{
					char* ObjName = CEngine::GetInst()->ConvertWCtoC(sheet->readStr(j, 0));

					m_vecDataName.push_back(ObjName);

					ObjListBox->AddItem(ObjName);

					DataInfo Data;

					Data.Name = ObjName;

					Data.HP = (int)sheet->readNum(j, 1);
					Data.MP = (int)sheet->readNum(j, 2);

					Data.Attack = (int)sheet->readNum(j, 3);
					Data.Armor = (int)sheet->readNum(j, 4);

					Data.Level = (int)sheet->readNum(j, 5);

					Data.Exp = (int)sheet->readNum(j, 6);

					m_mapData.insert(std::make_pair(ObjName, Data));
				}
			}

			m_mapSheet.insert(std::make_pair(str, m_vecDataName));
		}
	}

	book->release();

	ClosePopup();
}

