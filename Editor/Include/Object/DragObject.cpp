#include "DragObject.h"
#include "Component/StaticMeshComponent.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CDragObject::CDragObject()
{
	SetTypeID<CDragObject>();
}

CDragObject::CDragObject(const CDragObject& obj) : CGameObject(obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_Camera = (CCameraComponent*)FindComponent("DragCamera");
}

CDragObject::~CDragObject()
{
}

void CDragObject::SetStartPos(const Vector2& Pos)
{
	m_StartPos = Pos;
	m_Mesh->SetWorldPos(m_StartPos.x, m_StartPos.y, 0.f);
}

void CDragObject::SetEndPos(const Vector2& Pos)
{
	m_EndPos = Pos;

	m_Mesh->SetWorldScale(m_EndPos.x - m_StartPos.x, m_EndPos.y - m_StartPos.y, 1.f);
}

void CDragObject::Start()
{
	CGameObject::Start();

	if (m_Scene->GetCameraManager())
	{
		m_Scene->GetCameraManager()->KeepCamera();
	}

	m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);
}

bool CDragObject::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_Camera = CreateComponent<CCameraComponent>("DragCamera");

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_Camera);

	m_Mesh->SetLayerName("DragLayer");
	m_Mesh->SetMesh("FrameRect");
	m_Mesh->GetMaterial()->SetShader("PosMeshShader");
	m_Mesh->SetPivot(0.f, 1.f, 0.f);
	m_Mesh->SetBaseColor(1.f, 0.f, 1.f, 1.f);

	m_Camera->OnViewportCenter();

	return true;
}

void CDragObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CDragObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDragObject* CDragObject::Clone()
{
	return new CDragObject(*this);
}
