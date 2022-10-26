#pragma once

#include "Scene/SceneMode.h"

class CLoadingBalrogGate :
    public CSceneMode
{
public:
    CLoadingBalrogGate();
    ~CLoadingBalrogGate();

private:
    //CSharedPtr<CLoadingWidget> m_LoadingWidget;
    class CBalrogGateThread* m_LoadingThread;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

