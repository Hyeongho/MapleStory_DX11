#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CTauromacis :
    public CMonsterManager
{
public:
	CTauromacis();
	CTauromacis(const CTauromacis& obj);
	virtual ~CTauromacis();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;
	CSharedPtr<CColliderBox2D> m_AttackBody;
	CSharedPtr<CColliderBox2D> m_Sensor;
	CSharedPtr<CColliderBox2D> m_AttackRange;

	CSharedPtr<CSceneComponent> m_Muzzle;

	CAnimationSequence2DInstance* m_Anim;

	bool m_SolW;
	float m_WDistance;

	bool m_Hurt;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTauromacis* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AITrace(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

public:
	virtual float GetOpacity() const
	{
		if (!m_Sprite)
		{
			return 1.f;
		}

		return m_Sprite->GetOpacity();
	}

protected:
	virtual void CollisionCallbackBegin(const CollisionResult& result);
	void CollisionCallbackEnd(const CollisionResult& result);

private:
	void AttackBegin(const CollisionResult& result);
	void AttackEnd(const CollisionResult& result);

	void PlayAttackSound();

	virtual void Attack1Damage();
	virtual void AnimationFinish();
};

