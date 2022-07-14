#pragma once

#include "Scene/SceneMode.h"

class CLoadingSeolhuiui :
    public CSceneMode
{
public:
    CLoadingSeolhuiui();
    ~CLoadingSeolhuiui();

private:
    //CSharedPtr<CLoadingWidget> m_LoadingWidget;
    class CSeolhuiuiThread* m_LoadingThread;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

