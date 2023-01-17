#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"
#include "BalrogLeft.h"
#include "BalrogRight.h"
#include "AI/BalrogBT.h"
#include "../Widget/BossStatus.h"

class CBalrog :
    public CMonsterManager
{
public:
	CBalrog();
	CBalrog(const CBalrog& obj);
	virtual ~CBalrog();

private:
	std::thread t1;
	std::mutex m1;

	std::thread t2;
	std::mutex m2;

	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;
	CSharedPtr<CColliderBox2D> m_AttackBody;
	CSharedPtr<CColliderBox2D> m_Sensor;
	CSharedPtr<CColliderBox2D> m_AttackRange;

	CSharedPtr<CSceneComponent> m_LeftMuzzle;
	CSharedPtr<CSceneComponent> m_RightMuzzle;

	CAnimationSequence2DInstance* m_Anim;

	CBalrogLeft* m_BalrogLeft;
	CBalrogRight* m_BalrogRight;

	CBossStatus* m_BossStatus;

	CSharedPtr<CBalrogBT> m_BT;

	std::vector<float> m_Attack3AreaWarningPosX;

	bool m_BTRun;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBalrog* Clone();

public:
	CBalrogLeft* GetBalrogLeft() const
	{
		return m_BalrogLeft;
	}

	CBalrogRight* GetBalrogRight() const
	{
		return m_BalrogRight;
	}

	void SetBTRun(bool BTRun)
	{
		m_BTRun = BTRun;

		m_Body->SetExtent(414.f, 280.f);
	}

protected:
	virtual void AIIdle(float DeltaTime);
	virtual void AIAttack(float DeltaTime);
	virtual void AIDeath(float DeltaTime);

private:
	void InitAnimation();

	void AnimationFinish();
	void SetAttackRange();
	void Attack();

	void ChangeAnim(float DeltaTime);

	void PlayBodyAttack1AreaWarning();
	void PlayBodyAttack3AreaWarning();

	void PlayBalrogSound();

	void SceneChange();
};

