#pragma once

#include "GraphicShader.h"

class CWidgetShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CWidgetShader();
    virtual ~CWidgetShader();

public:
    virtual bool Init();
};

