#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CTaurospear :
    public CMonsterManager
{
public:
	CTaurospear();
	CTaurospear(const CTaurospear& obj);
	virtual ~CTaurospear();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;
	CSharedPtr<CColliderBox2D> m_Attack1Body;
	CSharedPtr<CColliderBox2D> m_Attack2Body;
	CSharedPtr<CColliderBox2D> m_Sensor;
	CSharedPtr<CColliderBox2D> m_AttackRange;

	CSharedPtr<CSceneComponent> m_Muzzle;

	CAnimationSequence2DInstance* m_Anim;

	bool m_SolW;
	float m_WDistance;
	float m_Opacity;

	bool m_Hurt1;
	bool m_Hurt2;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTaurospear* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AITrace(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

protected:
	void CollisionCallbackBegin(const CollisionResult& result);
	void CollisionCallbackEnd(const CollisionResult& result);

	void Attack1Begin(const CollisionResult& result);
	void Attack1End(const CollisionResult& result);

	void Attack2Begin(const CollisionResult& result);
	void Attack2End(const CollisionResult& result);

	void Attack1();
	void Attack2();

	void PlayAttackSound();
	virtual void AnimationFinish();
};

