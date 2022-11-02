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

	float m_TraceTime;
	float m_ActiveTime;
	float m_RandActive;
	int m_IsMove;	

	float m_Speed;

	Vector2 m_Size;
	class CPlayer2D* m_Player;

	bool m_Hurt;

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

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMonsterManager* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AITrace(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

public:
	bool CheckDie();

public:
	virtual void CollisionCallbackBegin(const CollisionResult& result);
	//virtual void CollisionCallbackEnd(const CollisionResult& result);

	virtual void AttackBegin(const CollisionResult& result);
	//virtual void AttackEnd(const CollisionResult& result);

	virtual void AnimationFinish();
};

