#pragma once

#include "Scene/SceneMode.h"
#include "Data/Data.h"

class CDefaultScene :
    public CSceneMode
{
public:
    CDefaultScene();
    ~CDefaultScene();

private:
    CSharedPtr<CData> m_Data;

public:
    virtual bool Init();

};
