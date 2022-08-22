#pragma once

#include "ObjectComponent.h"
#include "../GameInfo.h"

class CRigidBody :
	public CObjectComponent
{
	friend class CGameObject;

private:
	CRigidBody();
	CRigidBody(const CRigidBody& com);
	virtual ~CRigidBody();

private:
	CSharedPtr<class CSceneComponent> m_UpdateComponent;

private:
	Vector3 m_Force; // ũ��, ����
	Vector3 m_Accel; // ���ӵ�
	Vector3 m_AccelAlpha; // �߰� ���ӵ�
	Vector3 m_Velocity; // �ӵ�
	Vector3 m_MaxVelocity; // �ִ� �ӷ�

	float m_Mass; // ����
	float m_Speed; // �ӷ�
	float m_FricCoeffp; // �������

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

	void SetForce(Vector3 Force)
	{
		m_Force = Force;
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

	void AddVelocity(Vector3 Velocity)
	{
		m_Velocity += Velocity;
	}

	Vector3 GetVelocity() const
	{
		return m_Velocity;
	}

	void SetFricCoeffp(float FricCoeffp)
	{
		m_FricCoeffp = FricCoeffp;
	}

	void SetAccelAlpha(Vector3 AccelAlpha)
	{
		m_AccelAlpha = AccelAlpha;
	}

	void AddAccelAlpha(Vector3 AccelAlpha)
	{
		m_AccelAlpha += AccelAlpha;
	}

	void SetMaxVelocity(Vector3 MaxVelocity)
	{
		m_MaxVelocity = MaxVelocity;
	}

	Vector3 GetMaxVelocity() const
	{
		return m_MaxVelocity;
	}

private:
	void Move(float DeltaTime);

};

