#pragma once

#include "Node.h"

class CBalrogPaseChange :
    public CNode
{
public:
	CBalrogPaseChange();
	~CBalrogPaseChange();

private:
	class CBalrog* m_Balrog;

public:
	virtual bool Run();
};

