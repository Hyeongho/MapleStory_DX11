#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Button.h"
#include "Widget/Text.h"

class CTestWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
	CTestWidget();
	CTestWidget(const CTestWidget& window);
	virtual ~CTestWidget();



private:
	CSharedPtr<CButton>	m_Button1;
	CSharedPtr<CButton>	m_Button2;

	CSharedPtr<CText>	m_Button1Text;
	CSharedPtr<CText>	m_Button2Text;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CTestWidget* Clone();

public:
	void Button1Click();
	void Button2Click();
};

