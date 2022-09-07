#include "RigidBody.h"
#include "../Resource/Shader/TransformConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "CameraComponent.h"
#include "SceneComponent.h"
#include "../GameObject/GameObject.h"
#include "Gravity.h"

CRigidBody::CRigidBody() : m_Mass(1.f), m_FricCoeffp(Vector3(100.f, 100.f, 100.f)), m_MaxVelocity(Vector3(100.f, 600.f, 0.f)), m_Velocity(Vector3(0.f, 0.f, 0.f))
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
			m_Velocity.x += FricCoeffp.x;
			m_Velocity.y += FricCoeffp.y;
			m_Velocity.z += FricCoeffp.z;
		}
	}

	if (abs(m_Velocity.x) > abs(m_MaxVelocity.x))
	{
		m_Velocity.x = (m_Velocity.x / abs(m_Velocity.x)) * m_MaxVelocity.x;
	}

	if (abs(m_Velocity.y) > abs(m_MaxVelocity.y))
	{
		m_Velocity.y = (m_Velocity.y / abs(m_Velocity.y)) * m_MaxVelocity.y;
	}

	Move(DeltaTime);

	m_Force = Vector3(0.f, 0.f, 0.f);

	m_Accel = Vector3(0.f, 0.f, 0.f);
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

	CGravity* Gravity = m_Object->FindComponentFromType<CGravity>();

	if (Speed != 0.f)
	{
		Vector3 Dir = m_Velocity;
		Dir.Normalize();

		Vector3 Pos = m_UpdateComponent->GetWorldPos();

		Pos += m_Velocity * DeltaTime;

		/*Pos.x += m_Velocity.x * DeltaTime;

		if (Gravity)
		{
			if (Gravity->GetGround())
			{
				Pos.y = 0.f;
			}

			else
			{
				Pos.y += m_Velocity.y * DeltaTime;
			}
		}*/

		m_UpdateComponent->SetWorldPos(Pos);
	}
}
