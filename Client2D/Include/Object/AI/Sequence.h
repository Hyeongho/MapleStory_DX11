#pragma once

#include "CompositeNode.h"

class CSequence :
    public CCompositeNode
{
public:
    virtual bool Run();
};

