#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Number.h"

class CDamageWidget :
    public CWidgetWindow
{
    friend class CViewport;
    friend class CWidgetComponent;

protected:
    CDamageWidget();
    CDamageWidget(const CDamageWidget& window);
    virtual ~CDamageWidget();

private:
    CSharedPtr<CNumber> m_Number;

    std::vector<TCHAR*> m_vecFileName;

    float m_Opacity;

public:
    void SetNumber(float Damage);

    void SetOpacity(float Opacity)
    {
        m_Number->SetOpacity(Opacity);
    }

    float GetOpacity() const
    {
        return m_Number->GetOpacity();
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CDamageWidget* Clone();
};

