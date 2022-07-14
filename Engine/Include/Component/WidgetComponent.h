#pragma once

#include "SceneComponent.h"
#include "../Widget/WidgetWindow.h"
#include "../Scene/Scene.h"

class CWidgetComponent :
    public CSceneComponent
{
    friend class CGameObject;

protected:
    CWidgetComponent();
    CWidgetComponent(const CWidgetComponent& com);
    virtual ~CWidgetComponent();

protected:
    CSharedPtr<CWidgetWindow> m_WidgetWindow;
    WidgetComponent_Space m_Space;

public:
    void SetWidgetSpace(WidgetComponent_Space Space)
    {
        m_Space = Space;

        if (m_Space == WidgetComponent_Space::Screen)
        {
            SetInheritRotX(false);
            SetInheritRotY(false);
            SetInheritRotZ(false);
            SetLayerName("ScreenWidgetComponent");
        }

        else
        {
            SetInheritRotX(true);
            SetInheritRotY(true);
            SetInheritRotZ(true);
            SetLayerName("Default");
        }
    }

    WidgetComponent_Space GetWidgetSpace()  const
    {
        return m_Space;
    }

    void SetWidgetWindow(CWidgetWindow* Window)
    {
        if (m_WidgetWindow)
        {
            m_WidgetWindow->m_OwnerComponent = nullptr;
        }

        m_WidgetWindow = Window;

        m_WidgetWindow->m_OwnerComponent = this;
    }

    CWidgetWindow* GetWidgetWindow()    const
    {
        return m_WidgetWindow;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CWidgetComponent* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

public:
    template <typename T>
    T* CreateWidgetWindow(const std::string& Name)
    {
        T* Window = new T;

        Window->SetName(Name);
        Window->m_OwnerComponent = this;
        Window->m_Viewport = m_Scene->GetViewport();

        if (!Window->Init())
        {
            SAFE_RELEASE(Window);
            return nullptr;
        }

        m_WidgetWindow = Window;

        return Window;
    }
};

