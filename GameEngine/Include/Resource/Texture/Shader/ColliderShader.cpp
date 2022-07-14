#include "ColliderShader.h"

CColliderShader::CColliderShader()
{
	SetTypeID<CColliderShader>();
}

CColliderShader::~CColliderShader()
{
}

bool CColliderShader::Init()
{
	if (!LoadVertexShader("ColliderMeshVS", TEXT("Collider.fx"), SHADER_PATH))
	{
		return false;
	}

	if (!LoadPixelShader("ColliderMeshPS", TEXT("Collider.fx"), SHADER_PATH))
	{
		return false;
	}

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout())
	{
		return false;
	}

	return true;
}
