#pragma once
#include "GraphicShader.h"

class CParticleRenderShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CParticleRenderShader();
    virtual ~CParticleRenderShader();

public:
    virtual bool Init();
};

