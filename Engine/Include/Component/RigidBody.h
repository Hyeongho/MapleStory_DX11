#pragma once

#include "ObjectComponent.h"
#include "../GameInfo.h"

class CRigidBody :
	public CObjectComponent
{
	friend class CGameObject;

private:
	CRigidBody();
	CRigidBody(const CRigidBody& transform);
	virtual ~CRigidBody();

private:
	CSharedPtr<class CSceneComponent> m_UpdateComponent;

private:
	Vector3 m_Force; // 크기, 방향
	Vector3 m_Accel; // 가속도
	Vector3 m_Velocity; // 속도

	float m_Mass; // 질량
	float m_Speed; // 속력
	float m_MaxSpeed; // 최대 속력
	float m_FricCoeffp; // 마찰계수

public:
	void SetUpdateComponent(class CSceneComponent* UpdateComponent);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CRigidBody* Clone();

public:
	void AddForce(Vector3 Force)
	{
		m_Force += Force;
	}

	void SetMass(float Mass)
	{
		m_Mass = Mass;
	}
	
	float GetMass() const
	{
		return m_Mass;
	}

	void SetVelocity(Vector3 Velocity)
	{
		m_Velocity = Velocity;
	}

	void SetVelocity(float MaxSpeed)
	{
		m_MaxSpeed = MaxSpeed;
	}

private:
	void Move(float DeltaTime);

};

