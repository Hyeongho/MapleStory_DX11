#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/StartWidget.h"
#include "../Widget/Fade.h"

class CStartScene :
    public CSceneMode
{
public:
    CStartScene();
    ~CStartScene();

private:
    //CSharedPtr<CTestWidget> m_TestWidget;
    std::function<void(bool, float)> m_LoadingFunction;
    CSharedPtr<CFade> m_Fade;
    CSharedPtr<CStartWidget> m_StartWidget;

public:
    virtual void Start();
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void LoadSound();

public:
    template <typename T>
    void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
    {
        m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }
};

