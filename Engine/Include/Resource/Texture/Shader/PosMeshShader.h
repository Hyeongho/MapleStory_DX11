#pragma once

#include "GraphicShader.h"

class CPosMeshShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CPosMeshShader();
    virtual ~CPosMeshShader();

public:
    virtual bool Init();
};

