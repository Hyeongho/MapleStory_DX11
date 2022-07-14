#pragma once

#include "Scene/SceneMode.h"

class CLoadingAnotherDoor :
    public CSceneMode
{
public:
    CLoadingAnotherDoor();
    ~CLoadingAnotherDoor();

private:
    //CSharedPtr<CLoadingWidget> m_LoadingWidget;
    class CAnotherDoorThread* m_LoadingThread;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

