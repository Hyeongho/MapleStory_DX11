#pragma once

#include "GraphicShader.h"

class CMesh2DShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CMesh2DShader();
    virtual ~CMesh2DShader();

public:
    virtual bool Init();
};

