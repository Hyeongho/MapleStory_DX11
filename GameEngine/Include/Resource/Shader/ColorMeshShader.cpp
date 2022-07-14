#include "ColorMeshShader.h"

CColorMeshShader::CColorMeshShader()
{
	SetTypeID<CColorMeshShader>();
}

CColorMeshShader::~CColorMeshShader()
{
}

bool CColorMeshShader::Init()
{
	if (!LoadVertexShader("ColorMeshVS", TEXT("ColorMesh.fx"), SHADER_PATH))
	{
		return false;
	}
	
	if (!LoadPixelShader("ColorMeshPS", TEXT("ColorMesh.fx"), SHADER_PATH))
	{
		return false;
	}

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout())
	{
		return false;
	}

	return true;
}
