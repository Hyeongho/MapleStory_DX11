#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CBalrogLeft :
    public CMonsterManager
{
public:
	CBalrogLeft();
	CBalrogLeft(const CBalrogLeft& obj);
	virtual ~CBalrogLeft();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;
	CSharedPtr<CColliderBox2D> m_AttackBody;
	CSharedPtr<CColliderBox2D> m_Sensor;
	CSharedPtr<CColliderBox2D> m_AttackRange;

	CSharedPtr<CSceneComponent> m_Muzzle;

	CAnimationSequence2DInstance* m_Anim;

private:
	std::thread t1;
	std::mutex m1;

	std::vector<float> m_Attack1AreaWarningPosX;

	bool m_Target;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBalrogLeft* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

private:
	void InitAnimation();

	void ChangeAnim(float DeltaTime);

	void OnCollisionBegin(const CollisionResult& result);
	void OnCollisionEnd(const CollisionResult& result);

	void PlayLeftAttack1AreaWarning();

	void AnimationFinish();
	void ArmDie();

	void Attack();

	void PlayBalrogSound();
};

