#pragma once

#include "GameInfo.h"

class CDataManager
{
private:
	class CDataWindow* m_DataWindow;
	class CDataWindowTable* m_DataWindowTale;

public:
	bool Init(HINSTANCE hInst);
	void CreateDefaultSceneMode();
	int Run();

	DECLARE_SINGLE(CDataManager)
};

