#pragma once
#include "IMGUIWindow.h"
class CIMGUITestWindow :
    public CIMGUIWindow
{
public:
	CIMGUITestWindow();
	virtual ~CIMGUITestWindow();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);


public:
	void ClickButton1();
	void ClickButton2();
};

