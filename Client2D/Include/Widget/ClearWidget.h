#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"
#include "../ClientInfo.h"

class CClearWidget :
    public CWidgetWindow
{
	friend class CViewport;

protected:
	CClearWidget();
	CClearWidget(const CClearWidget& window);
	virtual ~CClearWidget();

private:
	CSharedPtr<CImage> m_Image;

	bool m_Play;
	float m_Delay;

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
	virtual CClearWidget* Clone();
};

