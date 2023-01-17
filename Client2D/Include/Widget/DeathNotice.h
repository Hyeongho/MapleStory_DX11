#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Button.h"
#include "Widget/Text.h"
#include "Widget/Image.h"

class CDeathNotice :
    public CWidgetWindow
{
    friend class CViewport;

protected:
	CDeathNotice();
	CDeathNotice(const CDeathNotice& window);
	virtual ~CDeathNotice();

private:
	CSharedPtr<CImage> m_Image;
	CSharedPtr<CButton> m_Button;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CDeathNotice* Clone();

public:
	void ClickCallBack();
};

