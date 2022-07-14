#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CShadowDualBlade :
    public CMonsterManager
{
public:
	CShadowDualBlade();
	CShadowDualBlade(const CShadowDualBlade& obj);
	virtual ~CShadowDualBlade();

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
	float m_Opacity;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CShadowDualBlade* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIMove(float DeltaTime);
	virtual void AITrace(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

private:
	void CreateAttackRange();

protected:
	virtual void CollisionCallbackBegin(const CollisionResult& result);
	void CollisionCallbackEnd(const CollisionResult& result);

	virtual void AttackBegin(const CollisionResult& result);
	void AttackEnd(const CollisionResult& result);

	virtual void AnimationFinish();
};

