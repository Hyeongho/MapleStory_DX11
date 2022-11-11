#pragma once

#include "../../ClientManager.h"
#include "Selector.h"
#include "Sequence.h"
#include "BalrogPaseChange.h"
#include "CheckBalrogHandDie.h"
#include "Ref.h"

class CBalrogBT : 
	public CRef
{
public:
	CBalrogBT();
	virtual ~CBalrogBT();

private:
	CSharedPtr<CSequence> m_Root;
	CSharedPtr<CSequence> m_Squence1;

	CSharedPtr<CSelector> m_Selector1;

	CSharedPtr<CCheckBalrogHandDie> m_CheckBalrogHandDie;
	
	CSharedPtr<CBalrogPaseChange> m_BalrogPaseChange;

public:
	void Start();
	void Run(bool IsRun = true);
};

