
#include "Mesh2DShader.h"

CMesh2DShader::CMesh2DShader()
{
	SetTypeID<CMesh2DShader>();
}

CMesh2DShader::~CMesh2DShader()
{
}

bool CMesh2DShader::Init()
{
	if (!LoadVertexShader("Mesh2DVS", TEXT("Mesh2D.fx"), SHADER_PATH))
	{
		return false;
	}

	if (!LoadPixelShader("Mesh2DPS", TEXT("Mesh2D.fx"), SHADER_PATH))
	{
		return false;
	}

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout())
	{
		return false;
	}

	return true;
}
