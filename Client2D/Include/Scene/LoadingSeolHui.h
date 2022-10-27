#pragma once

#include "Scene/SceneMode.h"

class CLoadingSeolHui :
    public CSceneMode
{
public:
    CLoadingSeolHui();
    ~CLoadingSeolHui();

private:
    //CSharedPtr<CLoadingWidget> m_LoadingWidget;
    class CSeolHuiThread* m_LoadingThread;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

