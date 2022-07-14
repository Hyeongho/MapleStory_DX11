
#include "ComputeShader.h"
#include "../../PathManager.h"
#include "../../Device.h"

CComputeShader::CComputeShader() : m_CS(nullptr), m_CSBlob(nullptr), m_EntryName{}, m_FileName{}
{
    m_Type = Shader_Type::Compute;
}

CComputeShader::CComputeShader(const CComputeShader& shader) : CShader(shader)
{
    m_CS = nullptr;
    m_CSBlob = nullptr;

    memcpy(m_EntryName, shader.m_EntryName, 64);
    memcpy(m_FileName, shader.m_FileName, MAX_PATH);
    m_PathName = shader.m_PathName;

    LoadComputeShader(shader.m_EntryName, shader.m_FileName, shader.m_PathName);
}

CComputeShader::~CComputeShader()
{
    SAFE_RELEASE(m_CS);
    SAFE_RELEASE(m_CSBlob);
}

void CComputeShader::SetShader()
{
    CDevice::GetInst()->GetContext()->CSSetShader(m_CS, nullptr, 0);
}

CComputeShader* CComputeShader::Clone()
{
    return nullptr;
}

bool CComputeShader::LoadComputeShader(const char* EntryName, const TCHAR* FileName, const std::string& PathName)
{
    SAFE_RELEASE(m_CS);
    SAFE_RELEASE(m_CSBlob);

    strcpy_s(m_EntryName, EntryName);
    lstrcpy(m_FileName, FileName);
    m_PathName = PathName;

    unsigned int Flag = 0;

#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

    TCHAR FullPath[MAX_PATH] = {};

    const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

    if (Info)
    {
        lstrcpy(FullPath, Info->Path);
    }

    lstrcat(FullPath, FileName);

    ID3DBlob* Error = nullptr;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "cs_5_0", Flag, 0, &m_CSBlob, &Error)))
    {
        OutputDebugStringA((char*)Error->GetBufferPointer());
        OutputDebugStringA("\n");

        return false;
    }

    // 컴파일된 코드를 이용해서 Shader를 만든다.
    if (FAILED(CDevice::GetInst()->GetDevice()->CreateComputeShader(m_CSBlob->GetBufferPointer(), m_CSBlob->GetBufferSize(), nullptr, &m_CS)))
    {
        return false;
    }

    return true;
}

void CComputeShader::Excute(unsigned int x, unsigned int y, unsigned int z)
{
    // ComputeShader를 실행시켜준다.
    SetShader();
    CDevice::GetInst()->GetContext()->Dispatch(x, y, z);
    CDevice::GetInst()->GetContext()->CSSetShader(nullptr, nullptr, 0);
}
