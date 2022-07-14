#include "PaperBurnComponent.h"
#include "../Resource/Material/Material.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Scene.h"

CPaperBurnComponent::CPaperBurnComponent()
{
	SetTypeID<CPaperBurnComponent>();
	m_CBuffer = new CPaperBurnConstantBuffer;

	m_CBuffer->Init();

	m_FinishTime = 2.f;

	m_StartPaperBurn = false;

	m_Filter = 0.f;
}

CPaperBurnComponent::CPaperBurnComponent(const CPaperBurnComponent& com) :
	CObjectComponent(com)
{
	m_CBuffer = com.m_CBuffer->Clone();

	m_FinishTime = com.m_FinishTime;
	m_Material = com.m_Material;
	m_StartPaperBurn = false;
	m_Filter = 0.f;
}

CPaperBurnComponent::~CPaperBurnComponent()
{
	SAFE_DELETE(m_CBuffer);

	if (m_Material)
	{
		m_Material->DeleteRenderCallback(this);
	}
}

void CPaperBurnComponent::StartPaperBurn()
{
	if (!m_Material || m_StartPaperBurn)
	{
		return;
	}

	m_Material->SetPaperBurn(true);
	m_StartPaperBurn = true;
}

void CPaperBurnComponent::SetMaterial(CMaterial* Material)
{
	m_Material = Material;

	m_Material->AddRenderCallback(this, &CPaperBurnComponent::SetShader);
}

void CPaperBurnComponent::SetInverse(bool Enable)
{
	m_CBuffer->SetInverse(Enable);
}

void CPaperBurnComponent::SetBurnTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
	{
		return;
	}

	m_BurnTexture = m_Scene->GetResource()->FindTexture(Name);
}

void CPaperBurnComponent::SetOutLineColor(const Vector4& Color)
{
	m_CBuffer->SetOutColor(Color);
}

void CPaperBurnComponent::SetOutLineColor(float r, float g, float b, float a)
{
	m_CBuffer->SetOutColor(r, g, b, a);
}

void CPaperBurnComponent::SetInLineColor(const Vector4& Color)
{
	m_CBuffer->SetInColor(Color);
}

void CPaperBurnComponent::SetInLineColor(float r, float g, float b, float a)
{
	m_CBuffer->SetInColor(r, g, b, a);
}

void CPaperBurnComponent::SetCenterLineColor(const Vector4& Color)
{
	m_CBuffer->SetCenterColor(Color);
}

void CPaperBurnComponent::SetCenterLineColor(float r, float g, float b, float a)
{
	m_CBuffer->SetCenterColor(r, g, b, a);
}

void CPaperBurnComponent::SetInFilter(float Filter)
{
	m_CBuffer->SetInFilter(Filter);
}

void CPaperBurnComponent::SetOutFilter(float Filter)
{
	m_CBuffer->SetOutFilter(Filter);
}

void CPaperBurnComponent::SetCenterFilter(float Filter)
{
	m_CBuffer->SetCenterFilter(Filter);
}

void CPaperBurnComponent::Start()
{
	CObjectComponent::Start();
}

bool CPaperBurnComponent::Init()
{
	SetBurnTexture("DefaultBurnTexture", TEXT("DefaultPaperBurn.png"));

	return true;
}

void CPaperBurnComponent::Update(float DeltaTime)
{
	if (m_StartPaperBurn)
	{
		m_Filter += DeltaTime / m_FinishTime;

		if (m_Filter >= 1.f)
		{
			m_Filter = 1.f;

			if (m_FinishCallback)
			{
				m_FinishCallback();
			}
		}

		m_CBuffer->SetFilter(m_Filter);
	}
}

void CPaperBurnComponent::PostUpdate(float DeltaTime)
{
}

void CPaperBurnComponent::PrevRender()
{
}

void CPaperBurnComponent::Render()
{
}

void CPaperBurnComponent::PostRender()
{
}

CPaperBurnComponent* CPaperBurnComponent::Clone()
{
	return new CPaperBurnComponent(*this);
}

void CPaperBurnComponent::SetShader()
{
	m_CBuffer->UpdateCBuffer();

	m_BurnTexture->SetShader(101, (int)Buffer_Shader_Type::Pixel, 0);
}
