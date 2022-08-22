#include "Gravity.h"
#include "../Resource/Shader/TransformConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "CameraComponent.h"
#include "SceneComponent.h"
#include "../GameObject/GameObject.h"
#include "RigidBody.h"

CGravity::CGravity() : m_Ground(false)
{
	SetTypeID<CGravity>();
}

CGravity::CGravity(const CGravity& com)
{
}

CGravity::~CGravity()
{
}

void CGravity::SetUpdateComponent(CSceneComponent* UpdateComponent)
{
	m_UpdateComponent = UpdateComponent;
}

void CGravity::SetGround(bool Ground)
{
	m_Ground = Ground;

	CRigidBody* RigidBody = m_Object->FindComponentFromType<CRigidBody>();

	if (!RigidBody)
	{
		return;
	}

	if (m_Ground)
	{
		Vector3 Velocity = RigidBody->GetVelocity();
		RigidBody->SetVelocity(Vector3(Velocity.x, 0.f, Velocity.z));
		RigidBody->SetForce(Vector3(Velocity.x, 0.f, Velocity.z));
		RigidBody->SetAccelAlpha(Vector3(Velocity.x, 0.f, Velocity.z));
	}
}

void CGravity::Start()
{
	if (!m_UpdateComponent)
	{
		m_UpdateComponent = m_Object->GetRootComponent();
	}
}

bool CGravity::Init()
{
	return true;
}

void CGravity::Update(float DeltaTime)
{
	
}

void CGravity::PostUpdate(float DeltaTime)
{
	CRigidBody* RigidBody = m_Object->FindComponentFromType<CRigidBody>();

	if (!RigidBody)
	{
		return;
	}

	if (m_Ground)
	{
		RigidBody->SetAccelAlpha(Vector3(0.f, 0.f, 0.f));
	}

	else
	{
		RigidBody->SetAccelAlpha(Vector3(0.f, -3000.f, 0.f));
	}
	
}

void CGravity::PrevRender()
{
}

void CGravity::Render()
{
}

void CGravity::PostRender()
{
}

CGravity* CGravity::Clone()
{
	return new CGravity(*this);
}