#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CBalrogRight :
    public CMonsterManager
{
public:
	CBalrogRight();
	CBalrogRight(const CBalrogRight& obj);
	virtual ~CBalrogRight();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;
	CSharedPtr<CColliderBox2D> m_AttackBody;
	CSharedPtr<CColliderBox2D> m_Sensor;
	CSharedPtr<CColliderBox2D> m_AttackRange;

	CSharedPtr<CSceneComponent> m_Muzzle;

	CAnimationSequence2DInstance* m_Anim;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBalrogRight* Clone();

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

private:
	void InitAnimation();

	void ChangeAnim(float DeltaTime);

	void AnimationFinish();
	void ArmDie();
};

