#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/TestWidget.h"

class CTestScene :
    public CSceneMode
{
public:
    CTestScene();
    ~CTestScene();

private:
    CSharedPtr<CTestWidget> m_TestWidget;
    std::function<void(bool, float)> m_LoadingFunction;

public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();

public:
    template <typename T>
    void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
    {
        m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }
};

