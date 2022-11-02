#pragma once

#include "Node.h"

class CCheckBalrogHandDie :
    public CNode
{
public:
	CCheckBalrogHandDie();
	~CCheckBalrogHandDie();

private:
	class CBalrog* m_Balrog;

public:
	virtual bool Run();
};

