#include "ShaderManager.h"
#include "ColorMeshShader.h"
#include "ConstantBuffer.h"
#include "Mesh2DShader.h"
#include "PosMeshShader.h"
#include "ColliderShader.h"
#include "ColliderPixelShader.h"
#include "WidgetShader.h"
#include "ProgressBarShader.h"
#include "NumberShader.h"
#include "ParticleUpdateShader.h"
#include "ParticleRenderShader.h"
#include "TileMapShader.h"

CShaderManager::CShaderManager()
{
}

CShaderManager::~CShaderManager()
{
}

bool CShaderManager::Init()
{
	if (!CreateShader<CColorMeshShader>("ColorMeshShader"))
	{
		return false;
	}

	if (!CreateShader<CPosMeshShader>("PosMeshShader"))
	{
		return false;
	}

	if (!CreateShader<CMesh2DShader>("Mesh2DShader"))
	{
		return false;
	}

	if (!CreateShader<CColliderShader>("ColliderShader"))
	{
		return false;
	}

	if (!CreateShader<CColliderPixelShader>("ColliderPixelShader"))
	{
		return false;
	}

	if (!CreateShader<CWidgetShader>("WidgetShader"))
	{
		return false;
	}

	if (!CreateShader<CProgressBarShader>("ProgressBarShader"))
	{
		return false;
	}

	if (!CreateShader<CNumberShader>("NumberShader"))
	{
		return false;
	}

	if (!CreateShader<CParticleUpdateShader>("ParticleUpdateShader"))
	{
		return false;
	}

	if (!CreateShader<CParticleRenderShader>("ParticleRenderShader"))
	{
		return false;
	}

	if (!CreateShader<CTileMapShader>("TileMapShader"))
	{
		return false;
	}

	// =================== 상수버퍼 ===================
	CreateConstantBuffer("TransformCBuffer", sizeof(TransformCBuffer), 0, (int)Buffer_Shader_Type::Graphic);

	CreateConstantBuffer("MaterialCBuffer", sizeof(MaterialCBuffer), 1, (int)Buffer_Shader_Type::Graphic);

	CreateConstantBuffer("Standard2DCBuffer", sizeof(Standard2DCBuffer), 2, (int)Buffer_Shader_Type::Graphic);

	CreateConstantBuffer("GlobalCBuffer", sizeof(GlobalCBuffer), 3, (int)Buffer_Shader_Type::All);

	CreateConstantBuffer("PaperBurnCBuffer", sizeof(PaperBurnCBuffer), 4, (int)Buffer_Shader_Type::Pixel);

	CreateConstantBuffer("Animation2DCBuffer", sizeof(Animation2DCBuffer), 10, (int)Buffer_Shader_Type::Graphic);

	CreateConstantBuffer("ColliderCBuffer", sizeof(ColliderCBuffer), 11, (int)Buffer_Shader_Type::Graphic);

	CreateConstantBuffer("WidgetCBuffer", sizeof(WidgetCBuffer), 11, (int)Buffer_Shader_Type::Graphic);

	CreateConstantBuffer("ProgressBarCBuffer", sizeof(ProgressBarCBuffer), 12, (int)Buffer_Shader_Type::Graphic);

	CreateConstantBuffer("ParticleCBuffer", sizeof(ParticleCBuffer), 11, (int)Buffer_Shader_Type::Compute);

	CreateConstantBuffer("TileMapCBuffer", sizeof(TileMapCBuffer), 11, (int)Buffer_Shader_Type::Graphic);

	return true;
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	auto iter = m_mapShader.find(Name);

	if (iter == m_mapShader.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CShaderManager::ReleaseShader(const std::string& Name)
{
	auto iter = m_mapShader.find(Name);

	if (iter != m_mapShader.end())
	{
		if (iter->second->GetRefCount() == 1)
		{
			m_mapShader.erase(iter);
		}
	}
}

bool CShaderManager::CreateConstantBuffer(const std::string& Name, int Size, int Register, int ConstantBufferShaderType)
{
	CConstantBuffer* Buffer = FindConstantBuffer(Name);

	if (Buffer)
	{
		return true;
	}

	Buffer = new CConstantBuffer;

	Buffer->SetName(Name);

	if (!Buffer->Init(Size, Register, ConstantBufferShaderType))
	{
		SAFE_RELEASE(Buffer);
		return false;
	}

	m_mapConstantBuffer.insert(std::make_pair(Name, Buffer));

	return true;
}

CConstantBuffer* CShaderManager::FindConstantBuffer(const std::string& Name)
{
	auto iter = m_mapConstantBuffer.find(Name);

	if (iter == m_mapConstantBuffer.end())
	{
		return nullptr;
	}

	return iter->second;
}
