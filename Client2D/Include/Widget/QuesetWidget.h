#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Text.h"

class CQuesetWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
	CQuesetWidget();
	CQuesetWidget(const CQuesetWidget& window);
	virtual ~CQuesetWidget();

private:
	CSharedPtr<CText> m_Text;

	float m_Opacity;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CQuesetWidget* Clone();

public:
	void SetText(std::string Text);
};

