#pragma once

#include "../../Ref.h"

class CConstantBuffer :
    public CRef
{
    friend class CShaderManager;

private:
    CConstantBuffer();
    ~CConstantBuffer();

private:
    ID3D11Buffer* m_Buffer;
    int m_Size;
    int m_Register;
    int m_ConstantBufferShaderType;

public:
    bool Init(int Size, int Register, int ConstantBufferShaderType);
    void UpdateBuffer(void* Data);
};

