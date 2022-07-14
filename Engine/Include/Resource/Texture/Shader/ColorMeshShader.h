#pragma once
#include "GraphicShader.h"
class CColorMeshShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CColorMeshShader();
    virtual ~CColorMeshShader();

public:
    virtual bool Init();
};

