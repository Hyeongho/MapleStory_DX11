#pragma once

#include "Scene/SceneMode.h"

class CLoadingBalrogAltar :
    public CSceneMode
{
public:
    CLoadingBalrogAltar();
    ~CLoadingBalrogAltar();

private:
    //CSharedPtr<CLoadingWidget> m_LoadingWidget;
    class CBalrogAltarThread* m_LoadingThread;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

