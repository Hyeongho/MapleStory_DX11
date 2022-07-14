#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"

class CFade :
	public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;

protected:
	CFade();
	CFade(const CFade& window);
	virtual ~CFade();

private:
	CSharedPtr<CImage> m_FadeImage;
	float m_Opacity;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CFade* Clone();

public:
	void FadeIn();
	void FadeOut();
};