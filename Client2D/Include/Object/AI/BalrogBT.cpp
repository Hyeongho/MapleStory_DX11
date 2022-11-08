#include "BalrogBT.h"
#include "Selector.h"
#include "Sequence.h"
#include "BalrogPaseChange.h"
#include "CheckBalrogHandDie.h"

CBalrogBT::CBalrogBT()
{
	m_Root = new CSequence;
	m_Squence1 = new CSequence;

	m_Selector1 = new CSelector;

	m_CheckBalrogHandDie = new CCheckBalrogHandDie;

	m_BalrogPaseChange = new CBalrogPaseChange;
}

CBalrogBT::~CBalrogBT()
{
	SAFE_DELETE(m_BalrogPaseChange);
	SAFE_DELETE(m_CheckBalrogHandDie);
	SAFE_DELETE(m_Selector1);
	SAFE_DELETE(m_Squence1);
	SAFE_DELETE(m_Root);
}

void CBalrogBT::Start()
{
	m_Root->AddChild(m_Selector1);

	m_Selector1->AddChild(m_Squence1);

	m_Squence1->AddChild(m_CheckBalrogHandDie);
	m_Squence1->AddChild(m_BalrogPaseChange);
}

void CBalrogBT::Run(bool IsRun)
{
	if (IsRun)
	{
		m_Root->Run();
	}
}
