#pragma once

#include "Data/Data.h"
#include "IMGUIWindow.h"

struct DataInfo
{
	int HP;
	int MP;

	int Exp;

	int Attack;
	int Armor;

	int Level;

	std::string Name;
	
	Object_Type ObjectType;

	DataInfo() : HP(0), MP(0), Exp(0), Attack(0), Armor(0), Level(1), Name{}, ObjectType(Object_Type::Player)
	{

	}
};

class CDataWindow :
	public CIMGUIWindow
{
public:
	CDataWindow();
	virtual ~CDataWindow();

private:
	class CDataModal* m_DataModal;

private:
	class CIMGUIMenuBar* m_MenuBar;

private:
	DataInfo m_DataInfo;
	std::vector<DataInfo> m_vecData;

private:
	class CIMGUIComboBox* m_TypeCombo;

	class CIMGUIText* m_TextHP;
	class CIMGUIText* m_TextMP;
	class CIMGUIText* m_TextExp;
	class CIMGUIText* m_TextAttack;
	class CIMGUIText* m_TextArmor;
	class CIMGUIText* m_TextLevel;
	class CIMGUIText* m_TextName;

	class CIMGUITextInput* m_InputHP;
	class CIMGUITextInput* m_InputMP;
	class CIMGUITextInput* m_InputExp;
	class CIMGUITextInput* m_InputAttack;
	class CIMGUITextInput* m_InputArmor;
	class CIMGUITextInput* m_InputLevel;
	class CIMGUITextInput* m_InputName;

	class CIMGUIButton* m_AddData;
	class CIMGUIButton* m_DeleteData;

	class CIMGUIButton* m_DataSaveButton;

private:
	class CIMGUIButton* m_SaveButton;
	class CIMGUIButton* m_LoadButton;

	class CIMGUIText* m_Text;

	class CIMGUITextInput* m_InputText;

private:
	class CData* m_Data;

	std::vector<std::string> m_vecDataName;

	std::unordered_map<std::string, std::vector<std::string>> m_mapSheet;
	std::unordered_map<std::string, DataInfo> m_mapData;

public:
	void SetDataInfo(DataInfo* Data);

public:
	DataInfo GetDataInfo() const
	{
		return m_DataInfo;
	}

	DataInfo GetDataInfo(int Index)
	{
		return m_vecData[Index];
	}

	std::vector<std::string> GetDataName() const
	{
		return m_vecDataName;
	}

	std::unordered_map<std::string, std::vector<std::string>> GetSheet() const
	{
		return m_mapSheet;
	}

	std::unordered_map<std::string, DataInfo> GetData() const
	{
		return m_mapData;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	std::vector<std::string> FindDataVector(std::string Name);
	DataInfo* FindData(std::string Name);

private:
	void CallBackName();
	void CallBackHP();
	void CallBackMP();
	void CallBackExp();
	void CallBackLevel();
	void CallBackAttack();
	void CallBackArmor();

	void AddCallback();
	void DeleteCallback();

	void SaveDataCallback();

private:
	void SelectMenu(int Index, std::string Label);

private:
	void SaveCallback();
	void LoadCallback();
};

