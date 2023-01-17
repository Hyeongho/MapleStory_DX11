#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"
#include "../ClientInfo.h"

class CClearFWidget :
    public CWidgetWindow
{
	friend class CViewport;

protected:
	CClearFWidget();
	CClearFWidget(const CClearFWidget& window);
	virtual ~CClearFWidget();

private:
	CSharedPtr<CImage> m_Image;

public:
	void SetEnable(bool Enable)
	{
		if (Enable)
		{
			m_Image->SetFrame(0);

			m_Image->Enable(true);
		}
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CClearFWidget* Clone();
};

