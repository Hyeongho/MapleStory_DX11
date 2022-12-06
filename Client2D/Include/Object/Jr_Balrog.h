#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CJr_Balrog :
    public CMonsterManager
{
public:
	CJr_Balrog();
	CJr_Balrog(const CJr_Balrog& obj);
	virtual ~CJr_Balrog();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;
	CSharedPtr<CColliderBox2D> m_AttackBody1;
	CSharedPtr<CColliderBox2D> m_AttackBody2;
	CSharedPtr<CColliderBox2D> m_AttackBody3;
	CSharedPtr<CColliderBox2D> m_Sensor;
	CSharedPtr<CColliderBox2D> m_AttackRange;

	CSharedPtr<CSceneComponent> m_Muzzle1;
	CSharedPtr<CSceneComponent> m_Muzzle2;
	CSharedPtr<CSceneComponent> m_Muzzle3;

	CSharedPtr<class CJr_BalrogAttack1Effect> m_Jr_BalrogAttack1Effect;
	CSharedPtr<class CJr_BalrogAttack2Effect> m_Jr_BalrogAttack2Effect;
	CSharedPtr<class CJr_BalrogAttack3Effect> m_Jr_BalrogAttack3Effect;

	CAnimationSequence2DInstance* m_Anim;

	bool m_Hurt;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CJr_Balrog* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AITrace(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

protected:
	virtual void CollisionCallbackBegin(const CollisionResult& result);
	void CollisionCallbackEnd(const CollisionResult& result);

	virtual void AttackBegin(const CollisionResult& result);
	void AttackEnd(const CollisionResult& result);

	virtual void AnimationFinish();

	void Attack1Effect();
	void Attack2Effect();
	void Attack3Effect();

	void PlayAttackSound();
};

