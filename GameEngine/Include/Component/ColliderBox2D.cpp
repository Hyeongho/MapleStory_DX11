#include "ColliderBox2D.h"
#include "../Collision/Collision.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Shader/ColliderConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "CameraComponent.h"
#include "ColliderCircle.h"
#include "ColliderPixel.h"

CColliderBox2D::CColliderBox2D()
{
	SetTypeID<CColliderBox2D>();
	m_ComponentType = Component_Type::SceneComponent;
	m_Render = true;

	m_ColliderType = Collider_Type::Box2D;
}

CColliderBox2D::CColliderBox2D(const CColliderBox2D& com) : CColliderComponent(com)
{
	m_Info = com.m_Info;
}

CColliderBox2D::~CColliderBox2D()
{
}

void CColliderBox2D::Start()
{
	CColliderComponent::Start();
}

bool CColliderBox2D::Init()
{
	if (!CColliderComponent::Init())
	{
		return false;
	}

	m_Info.Axis[0] = Vector2(1.f, 0.f);
	m_Info.Axis[1] = Vector2(0.f, 1.f);

	m_Info.Length = Vector2(50.f, 50.f);

	SetInheritRotZ(true);

	SetWorldScale(m_Info.Length.x * 2.f, m_Info.Length.y * 2.f, 1.f);

	m_Mesh = m_Scene->GetResource()->FindMesh("Box2D");

	return true;
}

void CColliderBox2D::Update(float DeltaTime)
{
	CColliderComponent::Update(DeltaTime);
}

void CColliderBox2D::PostUpdate(float DeltaTime)
{
	CColliderComponent::PostUpdate(DeltaTime);

	m_Info.Center.x = GetWorldPos().x + m_Offset.x;
	m_Info.Center.y = GetWorldPos().y + m_Offset.y;

	m_Info.Axis[0].x = GetWorldAxis(AXIS_X).x;
	m_Info.Axis[0].y = GetWorldAxis(AXIS_X).y;

	m_Info.Axis[1].x = GetWorldAxis(AXIS_Y).x;
	m_Info.Axis[1].y = GetWorldAxis(AXIS_Y).y;

	Vector2	Pos[4] = {};

	Pos[0] = m_Info.Center - m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y;
	Pos[1] = m_Info.Center + m_Info.Axis[0] * m_Info.Length.x + m_Info.Axis[1] * m_Info.Length.y;
	Pos[2] = m_Info.Center - m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y;
	Pos[3] = m_Info.Center + m_Info.Axis[0] * m_Info.Length.x - m_Info.Axis[1] * m_Info.Length.y;

	m_Min.x = Pos[0].x;
	m_Min.y = Pos[0].y;

	m_Max.x = Pos[0].x;
	m_Max.y = Pos[0].y;

	for (int i = 1; i < 4; ++i)
	{
		if (m_Min.x > Pos[i].x)
		{
			m_Min.x = Pos[i].x;
		}

		if (m_Min.y > Pos[i].y)
		{
			m_Min.y = Pos[i].y;
		}

		if (m_Max.x < Pos[i].x)
		{
			m_Max.x = Pos[i].x;
		}

		if (m_Max.y < Pos[i].y)
		{
			m_Max.y = Pos[i].y;
		}
	}

	m_Info.Min.x = m_Min.x;
	m_Info.Min.y = m_Min.y;

	m_Info.Max.x = m_Max.x;
	m_Info.Max.y = m_Max.y;
}

void CColliderBox2D::PrevRender()
{
	CColliderComponent::PrevRender();
}

void CColliderBox2D::Render()
{
	CColliderComponent::Render();

	CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

	Matrix	matWorld, matView, matProj, matWVP;

	matView = Camera->GetViewMatrix();
	matProj = Camera->GetProjMatrix();

	Matrix	matScale, matRot, matTrans;

	matScale.Scaling(m_Info.Length.x * 2.f, m_Info.Length.y * 2.f, 1.f);
	matRot.Rotation(GetWorldRot());
	matTrans.Translation(m_Info.Center);

	matWorld = matScale * matRot * matTrans;

	matWVP = matWorld * matView * matProj;

	matWVP.Transpose();

	m_CBuffer->SetWVP(matWVP);

	if (m_PrevCollisionList.empty())
	{
		m_CBuffer->SetColliderColor(Vector4(0.f, 1.f, 0.f, 1.f));
	}

	else
	{
		m_CBuffer->SetColliderColor(Vector4(1.f, 0.f, 0.f, 1.f));
	}

	if (m_MouseCollision)
	{
		m_CBuffer->SetColliderColor(Vector4(1.f, 0.f, 0.f, 1.f));
	}

	m_CBuffer->UpdateCBuffer();

	m_Shader->SetShader();

	m_Mesh->Render();
}

void CColliderBox2D::PostRender()
{
	CColliderComponent::PostRender();
}

CColliderBox2D* CColliderBox2D::Clone()
{
	return new CColliderBox2D(*this);
}

void CColliderBox2D::Save(FILE* File)
{
	CColliderComponent::Save(File);

	fwrite(&m_Info, sizeof(Box2DInfo), 1, File);
}

void CColliderBox2D::Load(FILE* File)
{
	CColliderComponent::Load(File);

	fread(&m_Info, sizeof(Box2DInfo), 1, File);
}

bool CColliderBox2D::Collision(CColliderComponent* Dest)
{
	switch (Dest->GetColliderType())
	{
	case Collider_Type::Box2D:
		return CCollision::CollisionBox2DToBox2D(this, (CColliderBox2D*)Dest);
	case Collider_Type::Circle:
		return CCollision::CollisionBox2DToCircle(this, (CColliderCircle*)Dest);
	case Collider_Type::Pixel:
		return CCollision::CollisionBox2DToPixel(this, (CColliderPixel*)Dest);
	}

	return false;
}

bool CColliderBox2D::CollisionMouse(const Vector2& MousePos)
{
	CollisionResult	result;

	m_MouseCollision = CCollision::CollisionBox2DToPoint(m_MouseResult, result, m_Info, MousePos);

	return m_MouseCollision;
}
