#pragma once

#include "IMGUIWidget.h"

class CIMGUISeparator :
    public CIMGUIWidget
{
    friend class CIMGUIWindow;
    friend class CIMGUIModal;

protected:
    CIMGUISeparator();
    virtual ~CIMGUISeparator();

public:
    virtual bool Init();
    virtual void Render();
};

