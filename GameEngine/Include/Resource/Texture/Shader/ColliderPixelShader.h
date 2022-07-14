#pragma once

#include "GraphicShader.h"

class CColliderPixelShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CColliderPixelShader();
    virtual ~CColliderPixelShader();

public:
    virtual bool Init();
};

