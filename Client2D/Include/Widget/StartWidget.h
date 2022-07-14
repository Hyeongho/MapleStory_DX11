#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Button.h"
#include "Widget/Text.h"
#include "Widget/Image.h"

class CStartWidget :
    public CWidgetWindow
{
	friend class CViewport;

protected:
	CStartWidget();
	CStartWidget(const CStartWidget& window);
	virtual ~CStartWidget();

private:
	CSharedPtr<CButton>	m_Male;
	CSharedPtr<CButton>	m_Female;
	CSharedPtr<CImage>	m_Back;

	CSharedPtr<CText> m_MaleText;
	CSharedPtr<CText> m_FemaleText;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CStartWidget* Clone();

public:
	void MaleClick();
	void FemaleClick();
};

