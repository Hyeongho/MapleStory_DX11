#pragma once

#include "ClientInfo.h"
#include "Data/Data.h"

class CTalkManager
{
private:
	std::vector<std::string> m_vecTalk;
	std::unordered_map<int, std::vector<const TCHAR*>> m_mapTalk;
	
public:
	bool Init();

public:
	void SetTalk(int ID, std::vector<const TCHAR*> Talk);

	std::unordered_map<int, std::vector<const TCHAR*>> GetTalk() const
	{
		return m_mapTalk;
	}

	std::vector<const TCHAR*> FindTalk(int ID);

private:
	void CreateTalk();

	DECLARE_SINGLE(CTalkManager)
};

