#pragma once

#include "ObjectManager.h"
#include "../ClientManager.h"
#include "../ClientInfo.h"

class CMonsterManager :
    public CObjectManager
{
public:
	CMonsterManager();
	CMonsterManager(const CMonsterManager& obj);
	virtual ~CMonsterManager();

protected:
	EMonster_State m_State;

	bool m_Flip;
	bool m_Trace;
	bool m_Stop;
	bool m_Attack;
	bool m_Die;

	float m_TraceTime;
	float m_ActiveTime;
	float m_RandActive;

	bool m_IsHide;
	float m_Opacity;

	int m_IsMove;	

	float m_Speed;

	Vector2 m_Size;
	class CPlayer2D* m_Player;

public:
	void SetSize(float x, float y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}

	void SetSize(const Vector2 Size)
	{
		m_Size = Size;
	}

	Vector2 GetSize() const
	{
		return m_Size;
	}

	void SetState(EMonster_State State)
	{
		m_State = State;
	}

	EMonster_State GetState() const
	{
		return m_State;
	}

	void SetDie(bool Die)
	{
		m_Die = Die;
	}

	bool GetFlip() const
	{
		return m_Flip;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMonsterManager* Clone();

public:
	virtual float GetOpacity() const;

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AITrace(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

protected:
	virtual void LoadSound();

public:
	bool CheckDie();

public:
	virtual void CollisionCallbackBegin(const CollisionResult& result);
	//virtual void CollisionCallbackEnd(const CollisionResult& result);

	virtual void AttackBegin(const CollisionResult& result);
	//virtual void AttackEnd(const CollisionResult& result);

	virtual void AnimationFinish();
};

