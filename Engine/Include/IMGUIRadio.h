#pragma once

#include "IMGUIWidget.h"

class CIMGUIRadio :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;
	friend class CIMGUIModal;

protected:
	CIMGUIRadio();
	virtual ~CIMGUIRadio();

public:
	virtual bool Init();
	virtual void Render();
};

