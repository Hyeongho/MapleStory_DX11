#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/ProgressBar.h"
#include "Widget/Image.h"
#include "../ClientInfo.h"

class CPlayerStatus :
    public CWidgetWindow
{
    friend class CViewport;
    friend class CWidgetComponent;

protected:
	CPlayerStatus();
	CPlayerStatus(const CPlayerStatus& window);
	virtual ~CPlayerStatus();

private:
	CSharedPtr<CImage> m_StausCover;
	CSharedPtr<CImage> m_StausBackGrond;
	CSharedPtr<CProgressBar> m_HPBar;
	CSharedPtr<CProgressBar> m_MPBar;

public:
	void SetText(const TCHAR* Text);
	void SetHPPercent(float Percent);
	void SetHPDir(ProgressBar_Dir Dir);

	void SetMPPercent(float Percent);
	void SetMPDir(ProgressBar_Dir Dir);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CPlayerStatus* Clone();
};

