#pragma once

#include "../../ClientManager.h"
#include "Ref.h"

class CNode :
	public CRef
{
public:
	virtual bool Run() = 0;
};

