#include "EffectComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Animation/AnimationSequence2DInstance.h"
#include "../Render/RenderManager.h"
#include "../Resource/Shader/Standard2DConstantBuffer.h"
#include "../Scene/SceneManager.h"

CEffectComponent::CEffectComponent() : m_Animation(nullptr)
{
	SetTypeID<CEffectComponent>();
	m_Render = true;

	m_LayerName = "Effect";
}

CEffectComponent::CEffectComponent(const CEffectComponent& com) : CSceneComponent(com)
{
	m_Mesh = com.m_Mesh;

	if (com.m_Animation)
	{
		m_Animation = com.m_Animation->Clone();
	}

	if (com.m_Material)
	{
		m_Material = com.m_Material->Clone();
	}
}

CEffectComponent::~CEffectComponent()
{
	SAFE_DELETE(m_Animation);
}

void CEffectComponent::SetMaterial(CMaterial* Material)
{
	m_Material = Material->Clone();

	m_Material->SetScene(m_Scene);
}

void CEffectComponent::SetBaseColor(const Vector4& Color)
{
	m_Material->SetBaseColor(Color);
}

void CEffectComponent::SetBaseColor(float r, float g, float b, float a)
{
	m_Material->SetBaseColor(r, g, b, a);
}

void CEffectComponent::SetRenderState(CRenderState* State)
{
	m_Material->SetRenderState(State);
}

void CEffectComponent::SetRenderState(const std::string& Name)
{
	m_Material->SetRenderState(Name);
}

void CEffectComponent::SetTransparency(bool Enable)
{
	m_Material->SetTransparency(Enable);
}

void CEffectComponent::SetOpacity(float Opacity)
{
	m_Material->SetOpacity(Opacity);
}

void CEffectComponent::AddOpacity(float Opacity)
{
	m_Material->AddOpacity(Opacity);
}

void CEffectComponent::AddTexture(int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_Material->AddTexture(Register, ShaderType, Name, Texture);
}

void CEffectComponent::AddTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_Material->AddTexture(Register, ShaderType, Name, FileName, PathName);
}

void CEffectComponent::AddTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	m_Material->AddTextureFullPath(Register, ShaderType, Name, FullPath);
}

void CEffectComponent::AddTexture(int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_Material->AddTexture(Register, ShaderType, Name, vecFileName, PathName);
}

void CEffectComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, Texture);
}

void CEffectComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, FileName, PathName);
}

void CEffectComponent::SetTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	m_Material->SetTextureFullPath(Index, Register, ShaderType, Name, FullPath);
}

void CEffectComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, vecFileName, PathName);
}

void CEffectComponent::Start()
{
	CSceneComponent::Start();

	if (m_Animation)
	{
		m_Animation->Start();
	}
}

bool CEffectComponent::Init()
{
	m_Mesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh("SpriteMesh");
	SetMaterial(m_Scene->GetResource()->FindMaterial("BaseTexture"));

	SetMeshSize(1.f, 1.f, 0.f);
	SetWorldScale((float)m_Material->GetTextureWidth(), (float)m_Material->GetTextureHeight(), 1.f);

	return true;
}

void CEffectComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	if (m_Animation)
	{
		m_Animation->Update(DeltaTime);
	}
}

void CEffectComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CEffectComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CEffectComponent::Render()
{
	CSceneComponent::Render();

	if (m_Animation)
	{
		CRenderManager::GetInst()->GetStandard2DCBuffer()->SetAnimation2DEnable(m_Animation->GetAnimationCount() > 0);
		CRenderManager::GetInst()->GetStandard2DCBuffer()->UpdateCBuffer();

		m_Animation->SetShader();
	}

	m_Material->Render();

	m_Mesh->Render();

	m_Material->Reset();
}

void CEffectComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CEffectComponent* CEffectComponent::Clone()
{
	return new CEffectComponent(*this);
}

void CEffectComponent::Save(FILE* File)
{
	std::string	MeshName = m_Mesh->GetName();

	int	Length = (int)MeshName.length();

	fwrite(&Length, sizeof(int), 1, File);
	fwrite(MeshName.c_str(), sizeof(char), Length, File);

	m_Material->Save(File);

	bool AnimEnable = false;

	if (m_Animation)
	{
		AnimEnable = true;
	}

	fwrite(&AnimEnable, sizeof(bool), 1, File);

	if (m_Animation)
	{
		size_t TypeID = m_Animation->GetTypeID();
		fwrite(&TypeID, sizeof(size_t), 1, File);

		m_Animation->Save(File);
	}

	CSceneComponent::Save(File);
}

void CEffectComponent::Load(FILE* File)
{
	char MeshName[256] = {};

	int	Length = 0;

	fread(&Length, sizeof(int), 1, File);
	fread(MeshName, sizeof(char), Length, File);

	m_Mesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh(MeshName);

	m_Material = m_Scene->GetResource()->CreateMaterialEmpty<CMaterial>();

	m_Material->Load(File);

	bool AnimEnable = false;

	fread(&AnimEnable, sizeof(bool), 1, File);

	if (AnimEnable)
	{
		size_t TypeID = 0;
		fread(&TypeID, sizeof(size_t), 1, File);

		CSceneManager::GetInst()->CallCreateAnimInstance(this, TypeID);

		m_Animation->Load(File);
	}

	CSceneComponent::Load(File);
}
