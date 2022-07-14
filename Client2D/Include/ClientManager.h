#pragma once

#include "ClientInfo.h"
#include "Data/Data.h"

class CClientManager
{
protected:
	CharacterInfo m_CharacterInfo;

	std::vector<CharacterInfo> m_vecData;
	std::vector<std::string> m_vecDataName;

	std::unordered_map<std::string, std::vector<std::string>> m_mapSheet;
	std::unordered_map<std::string, CharacterInfo> m_mapData;

private:
	class CData* m_Data;
	bool m_Fade;
	EFade_State m_FadeState;

public:
	bool Init(HINSTANCE hInst);
	void CreateDefaultSceneMode();
	int Run();

	void CreateSceneMode(class CScene* Scene, size_t Type);
	class CGameObject* CreateObject(class CScene* Scene, size_t Type);
	class CComponent* CreateComponent(class CGameObject* Obj, size_t Type);

public:
	CharacterInfo FindData(const std::string& name);

public:
	void SetFade(bool Fade)
	{
		m_Fade = Fade;
	}

	void SetFadeState(EFade_State State)
	{
		m_FadeState = State;
	}

	bool GetFade() const
	{
		return m_Fade;
	}

	EFade_State GetFadeState() const
	{
		return m_FadeState;
	}

private:
	void LoadData();
	void LoadSound();

	DECLARE_SINGLE(CClientManager)
};

