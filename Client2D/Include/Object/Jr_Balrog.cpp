#include "Jr_Balrog.h"
#include "Jr_BalrogAttack1Effect.h"
#include "Jr_BalrogAttack2Effect.h"
#include "Jr_BalrogAttack3Effect.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"

CJr_Balrog::CJr_Balrog()
{
}

CJr_Balrog::CJr_Balrog(const CJr_Balrog& obj)
{
}

CJr_Balrog::~CJr_Balrog()
{
}

void CJr_Balrog::Start()
{
	CMonsterManager::Start();

	m_Jr_BalrogAttack1Effect = m_Scene->CreateGameObject<CJr_BalrogAttack1Effect>("Jr_BalrogAttack1Effect");
	m_Jr_BalrogAttack2Effect = m_Scene->CreateGameObject<CJr_BalrogAttack2Effect>("Jr_BalrogAttack2Effect");
	m_Jr_BalrogAttack3Effect = m_Scene->CreateGameObject<CJr_BalrogAttack3Effect>("Jr_BalrogAttack3Effect");
}

bool CJr_Balrog::Init()
{
	CMonsterManager::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Jr_Balrog");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	//m_Sensor = CreateComponent<CColliderBox2D>("Sensor");
	m_AttackBody = CreateComponent<CColliderBox2D>("AttackBody");
	m_AttackRange = CreateComponent<CColliderBox2D>("AttackRange");
	m_Muzzle1 = CreateComponent<CSceneComponent>("Jr_BalrogMuzzle1");
	m_Muzzle2 = CreateComponent<CSceneComponent>("Jr_BalrogMuzzle2");
	m_Muzzle3 = CreateComponent<CSceneComponent>("Jr_BalrogMuzzle3");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	//m_Sensor->SetCollisionProfile("Monster");
	m_AttackBody->SetCollisionProfile("MonsterAttack");
	m_AttackRange->SetCollisionProfile("MonsterAttack");

	m_AttackBody->AddCollisionCallback<CJr_Balrog>(Collision_State::Begin, this, &CMonsterManager::AttackBegin);
	m_AttackBody->AddCollisionCallback<CJr_Balrog>(Collision_State::End, this, &CJr_Balrog::AttackEnd);

	m_Sprite->SetRelativeScale(700.f, 700.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 150, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Muzzle2->SetRelativePos(0.f, 0.f, 1.f);
	m_Muzzle3->SetRelativePos(0.f, 0.f, 1.f);

	m_Sprite->AddChild(m_Body);
	//m_Sprite->AddChild(m_Sensor);
	m_Sprite->AddChild(m_AttackBody);
	m_Sprite->AddChild(m_AttackRange);
	m_Sprite->AddChild(m_Muzzle1);
	m_Sprite->AddChild(m_Muzzle2);
	m_Sprite->AddChild(m_Muzzle3);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogIdle.sqc"), ANIMATION_PATH, "Idle", true);
	m_Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogMove.sqc"), ANIMATION_PATH, "Walk", true);
	m_Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack1.sqc"), ANIMATION_PATH, "Attack1", false, 2.25f);
	m_Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack2.sqc"), ANIMATION_PATH, "Attack2", false);
	m_Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack3.sqc"), ANIMATION_PATH, "Attack3", false);
	/*m_Anim->AddAnimation("Jr_BalrogAttack2", "Attack2", false);
	m_Anim->AddAnimation("Jr_BalrogAttack3", "Attack3", false);*/
	m_Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogDie.sqc"), ANIMATION_PATH, "Die", false, 0.43f);

	m_Anim->AddNotify("Attack1", "AttackPlaySound", 0, this, &CJr_Balrog::PlayAttackSound);
	m_Anim->AddNotify("Attack2", "AttackPlaySound", 0, this, &CJr_Balrog::PlayAttackSound);
	m_Anim->AddNotify("Attack3", "AttackPlaySound", 0, this, &CJr_Balrog::PlayAttackSound);

	m_Anim->AddNotify("Attack1", "Attack1", 7, this, &CJr_Balrog::Attack1Effect);
	m_Anim->AddNotify("Attack2", "Attack2", 1, this, &CJr_Balrog::Attack2Effect);
	m_Anim->AddNotify("Attack3", "Attack3", 5, this, &CJr_Balrog::Attack3Effect);

	m_Anim->SetEndFunction<CJr_Balrog>("Attack1", this, &CJr_Balrog::AnimationFinish);
	m_Anim->SetEndFunction<CJr_Balrog>("Attack2", this, &CJr_Balrog::AnimationFinish);
	m_Anim->SetEndFunction<CJr_Balrog>("Attack3", this, &CJr_Balrog::AnimationFinish);

	m_Body->SetExtent(93.f, 61.f);

	m_AttackBody->SetExtent(404.f, 240.f);

	//m_Sensor->SetExtent(150.f, 30.5f);

	m_Speed = 200.f;

	SetGravityAccel(30.f);
	SetPhysicsSimulate(false);
	SetJumpVelocity(40.f);
	SetSideWallCheck(false);

	SetSize(m_Body->GetInfo().Length);

	SetCharacterInfo("Jr_Balrog");

	return true;
}

void CJr_Balrog::Update(float DeltaTime)
{
	CMonsterManager::Update(DeltaTime);

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}
}

void CJr_Balrog::PostUpdate(float DeltaTime)
{
	CMonsterManager::PostUpdate(DeltaTime);

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}
}

CJr_Balrog* CJr_Balrog::Clone()
{
	return new CJr_Balrog(*this);
}

void CJr_Balrog::AIIdle(float DeltaTime)
{
	CMonsterManager::AIIdle(DeltaTime);

	m_Anim->ChangeAnimation("Idle");
}

void CJr_Balrog::AIMove(float DeltaTime)
{
	CMonsterManager::AIMove(DeltaTime);

	m_Anim->ChangeAnimation("Walk");

	if (m_Stop)
	{
		return;
	}

	if (m_Flip)
	{
		m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * m_Speed * DeltaTime);
	}

	else
	{
		m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * -m_Speed * DeltaTime);
	}

	m_Anim->SetAnimFlip(m_Flip);
}

void CJr_Balrog::AITrace(float DeltaTime)
{
	CMonsterManager::AITrace(DeltaTime);

	m_Anim->ChangeAnimation("Walk");

	if (m_Stop)
	{
		return;
	}

	if (m_Flip)
	{
		m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * m_Speed * DeltaTime);
	}

	else
	{
		m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * -m_Speed * DeltaTime);
	}

	m_Anim->SetAnimFlip(m_Flip);
}

void CJr_Balrog::AIAttack(float DeltaTime)
{
	CMonsterManager::AIAttack(DeltaTime);

	if (m_Anim->CheckCurrentAnimation("Attack1") || m_Anim->CheckCurrentAnimation("Attack2") || m_Anim->CheckCurrentAnimation("Attack3"))
	{
		return;
	}

	m_Anim->SetAnimFlip(m_Flip);

	int num = (rand() % 3) + 1;

	if (num == 1)
	{
		m_Anim->ChangeAnimation("Attack1");

		CResourceManager::GetInst()->SoundPlay("Jr_BalrogAttack1");
	}

	else if (num == 2)
	{
		m_Anim->ChangeAnimation("Attack2");

		CResourceManager::GetInst()->SoundPlay("Jr_BalrogAttack2");
	}

	else
	{
		m_Anim->ChangeAnimation("Attack3");

		CResourceManager::GetInst()->SoundPlay("Jr_BalrogAttack3");
	}
}

void CJr_Balrog::AIDeath(float DeltaTime)
{
	CMonsterManager::AIDeath(DeltaTime);

	m_Body->Destroy();
	//m_Sensor->Destroy();
	m_AttackBody->Destroy();
	m_AttackRange->Destroy();

	m_Anim->ChangeAnimation("Die");
}

void CJr_Balrog::CollisionCallbackBegin(const CollisionResult& result)
{
	CMonsterManager::CollisionCallbackBegin(result);
}

void CJr_Balrog::CollisionCallbackEnd(const CollisionResult& result)
{
}

void CJr_Balrog::AttackBegin(const CollisionResult& result)
{
	CMonsterManager::AttackBegin(result);

	m_Attack = true;
	m_Hurt = true;
}

void CJr_Balrog::AttackEnd(const CollisionResult& result)
{
	m_Attack = false;
}

void CJr_Balrog::AnimationFinish()
{
	if (m_Attack)
	{
		int num = (rand() % 3) + 1;

		if (num == 1)
		{
			m_Anim->ChangeAnimation("Attack1");
		}

		else if (num == 2)
		{
			m_Anim->ChangeAnimation("Attack2");		
		}

		else
		{
			m_Anim->ChangeAnimation("Attack3");
		}
	}

	else
	{
		CMonsterManager::AnimationFinish();
	}

	m_Anim->SetAnimFlip(m_Flip);
}

void CJr_Balrog::Attack1Effect()
{
	m_Jr_BalrogAttack1Effect->SetEnable(this);

	if (m_Flip)
	{
		m_Muzzle1->SetRelativePos(-18.f, 29.f, 0.f);
	}

	else
	{
		m_Muzzle1->SetRelativePos(15.f, 24.f, 1.f);
	}

	m_Jr_BalrogAttack1Effect->SetWorldPos(m_Muzzle1->GetWorldPos());
}

void CJr_Balrog::Attack2Effect()
{
	m_Jr_BalrogAttack2Effect->SetEnable(this);

	if (m_Flip)
	{
		m_Muzzle2->SetRelativePos(14.f, 6.f, 1.f);
		
	}

	else
	{
		m_Muzzle2->SetRelativePos(-14.f, 6.f, 0.f);
	}

	m_Jr_BalrogAttack2Effect->SetWorldPos(m_Muzzle2->GetWorldPos());
}

void CJr_Balrog::Attack3Effect()
{
	m_Jr_BalrogAttack3Effect->SetEnable(this);

	if (m_Flip)
	{
		m_Muzzle3->SetRelativePos(0.f, 0.f, 0.f);
	}

	else
	{
		m_Muzzle3->SetRelativePos(0.f, 0.f, 1.f);
	}

	m_Jr_BalrogAttack3Effect->SetWorldPos(m_Muzzle3->GetWorldPos());
}

void CJr_Balrog::PlayAttackSound()
{
	if (m_Anim->CheckCurrentAnimation("Attack1"))
	{
		CResourceManager::GetInst()->SoundPlay("Jr_BalrogAttack1");
	}

	else if (m_Anim->CheckCurrentAnimation("Attack2"))
	{
		CResourceManager::GetInst()->SoundPlay("Jr_BalrogAttack2");
	}

	else if (m_Anim->CheckCurrentAnimation("Attack3"))
	{
		CResourceManager::GetInst()->SoundPlay("Jr_BalrogAttack3");
	}
}
