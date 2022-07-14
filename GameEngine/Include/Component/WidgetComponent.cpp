#include "WidgetComponent.h"
#include "CameraComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "../Render/RenderManager.h"
#include "../Device.h"
#include "../Engine.h"

CWidgetComponent::CWidgetComponent()
{
	SetTypeID<CWidgetComponent>();

	m_Space = WidgetComponent_Space::Screen;

	SetInheritRotX(false);
	SetInheritRotY(false);
	SetInheritRotZ(false);

	m_Render = true;
}

CWidgetComponent::CWidgetComponent(const CWidgetComponent& com) : CSceneComponent(com)
{
	m_Space = com.m_Space;

	if (m_Space == WidgetComponent_Space::Screen)
	{
		SetInheritRotX(false);
		SetInheritRotY(false);
		SetInheritRotZ(false);
	}

	else
	{
		SetInheritRotX(true);
		SetInheritRotY(true);
		SetInheritRotZ(true);
	}

	m_WidgetWindow = com.m_WidgetWindow->Clone();
	m_WidgetWindow->m_OwnerComponent = this;
}

CWidgetComponent::~CWidgetComponent()
{
}

void CWidgetComponent::Start()
{
	CSceneComponent::Start();
}

bool CWidgetComponent::Init()
{
	SetLayerName("ScreenWidgetComponent");

	return true;
}

void CWidgetComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	if (!m_WidgetWindow->GetVisibility())
	{
		return;
	}

	if (m_WidgetWindow)
	{
		m_WidgetWindow->Update(DeltaTime);
	}
}

void CWidgetComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	if (!m_WidgetWindow->GetVisibility())
	{
		return;
	}

	if (m_WidgetWindow)
	{
		// 월드공간에서의 위치 정보로 WidgetComponent의 위치 정보가 갱신되어 있을 것이다.
		// 이를 화면공간에서의 위치로 변환해 주어야 한다.
		// 월드 -> 뷰 -> 투영 변환 후에 화면공간으로 변환이 된다.
		// 화면공간으로 변환이 될때에는 투영으로 변환된 x, y, z, w 가 있을 경우 모든 요소들을
		// w로 나누어서 화면공간으로 변환을 시도한다.
		CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

		Matrix	matView = Camera->GetViewMatrix();
		Matrix	matProj = Camera->GetProjMatrix();
		Matrix	matVP = matView * matProj;

		Vector3	WorldPos = GetWorldPos();

		Vector3	ViewPos = WorldPos.TransformCoord(matView);

		Vector3	ProjPos = ViewPos.TransformCoord(matProj);

		if (m_Space == WidgetComponent_Space::World)
		{
			float w = ViewPos.x * matProj._14 + ViewPos.y * matProj._24 + ViewPos.z * matProj._34 + matProj._44;

			ProjPos.x /= w;
			ProjPos.y /= w;
			ProjPos.z /= w;
		}

		Resolution RS = CDevice::GetInst()->GetResolution();

		Vector2	ScreenPos;

		ScreenPos.x = ProjPos.x * (RS.Width / 2.f) + (RS.Width / 2.f);
		ScreenPos.y = ProjPos.y * (RS.Height / 2.f) + (RS.Height / 2.f);

		/*if (CEngine::GetInst()->GetEngineSpace() == Engine_Space::Space2D)
		{

		}

		else
		{
			ScreenPos.x = ProjPos.x * (RS.Width / 2.f) + (RS.Width / 2.f);
			ScreenPos.y = ProjPos.y * (RS.Height / -2.f) + (RS.Height / 2.f);
		}*/

		m_WidgetWindow->SetPos(ScreenPos);

		m_WidgetWindow->PostUpdate(DeltaTime);
	}
}

void CWidgetComponent::PrevRender()
{
	CSceneComponent::PrevRender();

	if (!m_WidgetWindow->GetVisibility())
	{
		return;
	}
}

void CWidgetComponent::Render()
{
	CSceneComponent::Render();

	if (!m_WidgetWindow->GetVisibility())
	{
		return;
	}

	CRenderManager::GetInst()->SetAlphaBlendState();

	m_WidgetWindow->Render();

	CRenderManager::GetInst()->ResetAlphaBlendState();
}

void CWidgetComponent::PostRender()
{
	CSceneComponent::PostRender();

	if (!m_WidgetWindow->GetVisibility())
	{
		return;
	}
}

CWidgetComponent* CWidgetComponent::Clone()
{
	return new CWidgetComponent(*this);
}

void CWidgetComponent::Save(FILE* File)
{
	CSceneComponent::Save(File);
}

void CWidgetComponent::Load(FILE* File)
{
	CSceneComponent::Load(File);
}
