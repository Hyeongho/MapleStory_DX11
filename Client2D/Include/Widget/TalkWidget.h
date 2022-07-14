#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Button.h"
#include "Widget/Text.h"
#include "Widget/Image.h"
#include "Widget/Button.h"

class CTalkWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
	CTalkWidget();
	CTalkWidget(const CTalkWidget& window);
	virtual ~CTalkWidget();

private:
	CSharedPtr<CImage> m_Back;
	CSharedPtr<CImage> m_NameTag;

	CSharedPtr<CText> m_Name;
	CSharedPtr<CText> m_Talk;

	CSharedPtr<CButton> m_Next;
	CSharedPtr<CButton> m_Prev;
	CSharedPtr<CButton> m_OK;

	int m_OutputText;
	int m_OutputIndex;

	std::vector<const TCHAR*> m_vecTalk;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CTalkWidget* Clone();

public:
	void SetTextName(TCHAR* Name);
	void SetTalk(int ID, const TCHAR* Name);

private:
	void NextClick();
	void OKClick();
};

