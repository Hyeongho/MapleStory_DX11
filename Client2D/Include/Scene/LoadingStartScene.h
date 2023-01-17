#pragma once

#include "Scene/SceneMode.h"

class CLoadingStartScene :
    public CSceneMode
{
public:
    CLoadingStartScene();
    ~CLoadingStartScene();

private:
    //CSharedPtr<CLoadingWidget> m_LoadingWidget;
    class CStartSceneThread* m_LoadingThread;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

