#include "SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Animation/AnimationSequence2DInstance.h"
#include "../Render/RenderManager.h"
#include "../Resource/Shader/Standard2DConstantBuffer.h"
#include "../Scene/SceneManager.h"

CSpriteComponent::CSpriteComponent() : m_Animation(nullptr)
{
	SetTypeID<CSpriteComponent>();
	m_Render = true;
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& com) : CSceneComponent(com)
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

CSpriteComponent::~CSpriteComponent()
{
	SAFE_DELETE(m_Animation);
}

void CSpriteComponent::SetMaterial(CMaterial* Material)
{
	m_Material = Material->Clone();

	m_Material->SetScene(m_Scene);
}

void CSpriteComponent::SetBaseColor(const Vector4& Color)
{
	m_Material->SetBaseColor(Color);
}

void CSpriteComponent::SetBaseColor(float r, float g, float b, float a)
{
	m_Material->SetBaseColor(r, g, b, a);
}

void CSpriteComponent::SetRenderState(CRenderState* State)
{
	m_Material->SetRenderState(State);
}

void CSpriteComponent::SetRenderState(const std::string& Name)
{
	m_Material->SetRenderState(Name);
}

void CSpriteComponent::SetTransparency(bool Enable)
{
	m_Material->SetTransparency(Enable);
}

void CSpriteComponent::SetOpacity(float Opacity)
{
	m_Material->SetOpacity(Opacity);
}

void CSpriteComponent::AddOpacity(float Opacity)
{
	m_Material->AddOpacity(Opacity);
}

void CSpriteComponent::AddTexture(int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_Material->AddTexture(Register, ShaderType, Name, Texture);
}

void CSpriteComponent::AddTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_Material->AddTexture(Register, ShaderType, Name, FileName, PathName);
}

void CSpriteComponent::AddTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	m_Material->AddTextureFullPath(Register, ShaderType, Name, FullPath);
}

void CSpriteComponent::AddTexture(int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_Material->AddTexture(Register, ShaderType, Name, vecFileName, PathName);
}

void CSpriteComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, Texture);
}

void CSpriteComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, FileName, PathName);
}

void CSpriteComponent::SetTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	m_Material->SetTextureFullPath(Index, Register, ShaderType, Name, FullPath);
}

void CSpriteComponent::SetTexture(int Index, int Register, int ShaderType, const std::string& Name,
	const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	m_Material->SetTexture(Index, Register, ShaderType, Name, vecFileName, PathName);
}

void CSpriteComponent::Start()
{
	CSceneComponent::Start();

	if (m_Animation)
	{
		m_Animation->Start();
	}
}

bool CSpriteComponent::Init()
{
	m_Mesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh("SpriteMesh");
	SetMaterial(m_Scene->GetResource()->FindMaterial("BaseTexture"));

	SetMeshSize(1.f, 1.f, 0.f);
	SetWorldScale((float)m_Material->GetTextureWidth(), (float)m_Material->GetTextureHeight(), 1.f);

	return true;
}

void CSpriteComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	if (m_Animation)
	{
		m_Animation->Update(DeltaTime);
	}
}

void CSpriteComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CSpriteComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CSpriteComponent::Render()
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

void CSpriteComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CSpriteComponent* CSpriteComponent::Clone()
{
	return new CSpriteComponent(*this);
}

void CSpriteComponent::Save(FILE* File)
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

void CSpriteComponent::Load(FILE* File)
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
