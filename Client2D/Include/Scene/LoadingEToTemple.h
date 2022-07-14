#pragma once

#include "Scene/SceneMode.h"

class CLoadingEToTemple :
    public CSceneMode
{
public:
    CLoadingEToTemple();
    ~CLoadingEToTemple();

private:
    //CSharedPtr<CLoadingWidget> m_LoadingWidget;
    class CEToTempleThread* m_LoadingThread;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

