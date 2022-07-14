#pragma once

#include "IMGUIWidget.h"

class CIMGUIGroup :
    public CIMGUIWidget
{
    friend class CIMGUIWindow;
    friend class CIMGUIModal;

protected:
    CIMGUIGroup();
    virtual ~CIMGUIGroup();

public:
    virtual bool Init();
    virtual void Render();
};

