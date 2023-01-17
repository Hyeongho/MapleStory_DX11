#include "Widget.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "../Component/CameraComponent.h"
#include "../Resource/Shader/WidgetConstantBuffer.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"

CWidget::CWidget() : m_Owner(nullptr), m_ZOrder(0), m_Start(false), m_Angle(0.f), m_CBuffer(nullptr), m_Size(50.f, 50.f), m_MouseHovered(false),
m_CollisionMouseEnable(true), m_Tint(1.f, 1.f, 1.f, 1.f), m_Opacity(1.f), m_Visibility(true)
{
}

CWidget::CWidget(const CWidget& widget)
{
	*this = widget;

	m_RefCount = 0;

	m_Owner = nullptr;
	m_MouseHovered = false;

	m_CBuffer = new CWidgetConstantBuffer;

	m_CBuffer->Init();
}

CWidget::~CWidget()
{
	SAFE_DELETE(m_CBuffer);
}

void CWidget::SetShader(const std::string& Name)
{
	if (m_Owner->GetViewport())
	{
		m_Shader = m_Owner->GetViewport()->GetScene()->GetResource()->FindShader(Name);
	}

	else
	{
		m_Shader = CResourceManager::GetInst()->FindShader(Name);
	}
}

void CWidget::SetUseTexture(bool Use)
{
	m_CBuffer->SetUseTexture(Use);
}

void CWidget::Start()
{
	m_Start = true;
}

bool CWidget::Init()
{
	if (m_Owner->GetViewport())
	{
		m_Shader = m_Owner->GetViewport()->GetScene()->GetResource()->FindShader("WidgetShader");
	}

	else
	{
		m_Shader = CResourceManager::GetInst()->FindShader("WidgetShader");
	}


	if (m_Owner->GetViewport())
	{
		m_Mesh = m_Owner->GetViewport()->GetScene()->GetResource()->FindMesh("WidgetMesh");
	}

	else
	{
		m_Mesh = CResourceManager::GetInst()->FindMesh("WidgetMesh");
	}

	m_CBuffer = new CWidgetConstantBuffer;

	m_CBuffer->Init();

	return true;
}

void CWidget::Update(float DeltaTime)
{
	if (!m_Start)
	{
		Start();
	}
}

void CWidget::PostUpdate(float DeltaTime)
{
	if (!m_Start)
	{
		Start();
	}

	m_RenderPos = m_Pos;

	if (m_Owner)
	{
		m_RenderPos += m_Owner->GetWindowPos();
	}
}

void CWidget::Render()
{
	if (!m_Start)
	{
		Start();
	}

	Matrix	matScale, matRot, matTrans;

	matScale.Scaling(m_Size.x, m_Size.y, 1.f);
	matRot.Rotation(0.f, 0.f, m_Angle);
	matTrans.Translation(m_RenderPos.x, m_RenderPos.y, 0.f);

	CCameraComponent* UICamera = nullptr;

	if (m_Owner->GetViewport())
	{
		UICamera = m_Owner->GetViewport()->GetScene()->GetCameraManager()->GetUICamera();
	}

	else
	{
		UICamera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetUICamera();
	}

	Matrix	matWP = matScale * matRot * matTrans * UICamera->GetProjMatrix();
	matWP.Transpose();

	m_CBuffer->SetWP(matWP);
	m_CBuffer->SetTint(m_Tint);
	m_CBuffer->SetOpacity(m_Opacity);

	m_CBuffer->UpdateCBuffer();

	m_Shader->SetShader();

	m_Mesh->Render();
}

bool CWidget::CollisionMouse(const Vector2& MousePos)
{
	if (!m_CollisionMouseEnable)
	{
		return false;
	}

	if (m_RenderPos.x > MousePos.x)
	{
		return false;
	}

	else if (m_RenderPos.x + m_Size.x < MousePos.x)
	{
		return false;
	}

	else if (m_RenderPos.y > MousePos.y)
	{
		return false;
	}

	else if (m_RenderPos.y + m_Size.y < MousePos.y)
	{
		return false;
	}

	return true;
}

CWidget* CWidget::Clone()
{
	return new CWidget(*this);
}
