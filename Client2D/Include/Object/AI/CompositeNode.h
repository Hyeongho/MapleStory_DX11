#pragma once

#include "Node.h"

class CCompositeNode :
    public CNode
{
private:
    std::vector<CNode*> m_Children;

public:
    std::vector<CNode*> GetChildren() const
    {
        return m_Children;
    }

    void AddChild(CNode* Child)
    {
        m_Children.emplace_back(Child);
    }
};