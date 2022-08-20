#include "RigidBody.h"
#include "../Resource/Shader/TransformConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "CameraComponent.h"
#include "SceneComponent.h"
#include "../GameObject/GameObject.h"

CRigidBody::CRigidBody() : m_Mass(1.f), m_FricCoeffp(100.f), m_MaxSpeed(100.f), m_Velocity(Vector3(0.f, 0.f, 0.f))
{
	SetTypeID<CRigidBody>();
}

CRigidBody::CRigidBody(const CRigidBody& com) : CObjectComponent(com)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::SetUpdateComponent(CSceneComponent* UpdateComponent)
{
	m_UpdateComponent = UpdateComponent;
}

void CRigidBody::Start()
{
	if (!m_UpdateComponent)
	{
		m_UpdateComponent = m_Object->GetRootComponent();
	}
}

bool CRigidBody::Init()
{
	return true;
}

void CRigidBody::Update(float DeltaTime)
{
}

void CRigidBody::PostUpdate(float DeltaTime)
{
	float Force = m_Force.Length();

	if (Force != 0.f)
	{
		m_Force.Normalize();

		float Accel = Force / m_Mass;

		m_Accel = m_Force * Accel;
	}

	m_Accel += m_AccelAlpha;

	m_Velocity += m_Accel * DeltaTime;

	if (m_Velocity.Length() != 0.f)
	{
		Vector3 FricDir = m_Velocity * -1.f;

		FricDir.Normalize();

		Vector3 FricCoeffp = FricDir * m_FricCoeffp * DeltaTime;

		if (FricCoeffp.Length() > m_Velocity.Length())
		{
			m_Velocity = Vector3(0.f, 0.f, 0.f);
		}

		else
		{
			m_Velocity += FricCoeffp;
		}
	}

	if (m_Velocity.Length() > m_MaxSpeed)
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxSpeed;
	}

	Move(DeltaTime);

	m_Force = Vector3(0.f, 0.f, 0.f);

	m_AccelAlpha = Vector3(0.f, 0.f, 0.f);
}

void CRigidBody::PrevRender()
{
}

void CRigidBody::Render()
{
}

void CRigidBody::PostRender()
{
}

CRigidBody* CRigidBody::Clone()
{
	return new CRigidBody(*this);
}

void CRigidBody::Move(float DeltaTime)
{
	float Speed = m_Velocity.Length();

	if (Speed != 0.f)
	{
		Vector3 Dir = m_Velocity;
		Dir.Normalize();

		Vector3 Pos = m_UpdateComponent->GetWorldPos();

		Pos += m_Velocity * DeltaTime;

		m_UpdateComponent->SetWorldPos(Pos);
	}
}
