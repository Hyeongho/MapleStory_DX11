#include "MaterialManager.h"
#include "../ResourceManager.h"
#include "../Shader/MaterialConstantBuffer.h"

CMaterialManager::CMaterialManager() : m_CBuffer(nullptr)
{
}

CMaterialManager::~CMaterialManager()
{
	SAFE_DELETE(m_CBuffer);
}

bool CMaterialManager::Init()
{
	m_CBuffer = new CMaterialConstantBuffer;

	m_CBuffer->Init();

	CreateMaterial<CMaterial>("Color");

	CSharedPtr<CMaterial> Mtrl = FindMaterial("Color");

	Mtrl->SetShader("ColorMeshShader");

	CreateMaterial<CMaterial>("BaseTexture");

	Mtrl = FindMaterial("BaseTexture");

	Mtrl->SetShader("Mesh2DShader");

	CTexture* Texture = CResourceManager::GetInst()->FindTexture("EngineTexture");

	Mtrl->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "EngineTexture", Texture);

	return true;
}

CMaterial* CMaterialManager::FindMaterial(const std::string& Name)
{
	auto iter = m_mapMaterial.find(Name);

	if (iter == m_mapMaterial.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CMaterialManager::ReleaseMaterial(const std::string& Name)
{
	auto iter = m_mapMaterial.find(Name);

	if (iter != m_mapMaterial.end())
	{
		if (iter->second->GetRefCount() == 1)
		{
			m_mapMaterial.erase(iter);
		}
	}
}
