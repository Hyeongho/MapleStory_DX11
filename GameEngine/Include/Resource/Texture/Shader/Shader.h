#pragma once

#include "../../Ref.h"

class CShader :
    public CRef
{
    friend class CShaderManager;

protected:
    CShader();
    CShader(const CShader& shader);
    virtual ~CShader() = 0;

protected:
    Shader_Type m_Type;

public:
    Shader_Type GetShaderType() const
    {
        return m_Type;
    }

public:
    virtual bool Init() = 0;
    virtual void SetShader() = 0;
};

