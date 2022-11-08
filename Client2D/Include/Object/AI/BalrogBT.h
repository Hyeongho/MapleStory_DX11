#pragma once

#include "../../ClientManager.h"

class CBalrogBT
{
public:
	CBalrogBT();
	~CBalrogBT();

private:
	class CSequence* m_Root;
	class CSequence* m_Squence1;

	class CSelector* m_Selector1;

	class CCheckBalrogHandDie* m_CheckBalrogHandDie;
	
	class CBalrogPaseChange* m_BalrogPaseChange;

public:
	void Start();
	void Run(bool IsRun = true);
};

