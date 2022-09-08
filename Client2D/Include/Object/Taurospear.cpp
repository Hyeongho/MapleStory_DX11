#include "Taurospear.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"

CTaurospear::CTaurospear()
{
}

CTaurospear::CTaurospear(const CTaurospear& obj)
{
}

CTaurospear::~CTaurospear()
{
}

void CTaurospear::Start()
{
}

bool CTaurospear::Init()
{
	CMonsterManager::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Taurospear");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sensor = CreateComponent<CColliderBox2D>("Sensor");
	m_AttackBody = CreateComponent<CColliderBox2D>("AttackBody");
	m_AttackRange = CreateComponent<CColliderBox2D>("AttackRange");
	m_Muzzle = CreateComponent<CSceneComponent>("TauromacisMuzzle");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	m_Sensor->SetCollisionProfile("Monster");
	m_AttackBody->SetCollisionProfile("MonsterAttack");
	m_AttackRange->SetCollisionProfile("MonsterAttack");

	m_Sensor->AddCollisionCallback<CTaurospear>(Collision_State::Begin, this, &CMonsterManager::CollisionCallbackBegin);
	m_Sensor->AddCollisionCallback<CTaurospear>(Collision_State::End, this, &CTaurospear::CollisionCallbackEnd);

	m_AttackBody->AddCollisionCallback<CTaurospear>(Collision_State::Begin, this, &CMonsterManager::AttackBegin);
	m_AttackBody->AddCollisionCallback<CTaurospear>(Collision_State::End, this, &CTaurospear::AttackEnd);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Sensor);
	m_Sprite->AddChild(m_AttackBody);
	m_Sprite->AddChild(m_AttackRange);
	m_Sprite->AddChild(m_Muzzle);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearIdle.sqc"), ANIMATION_PATH, "Idle", true);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearMove.sqc"), ANIMATION_PATH, "Walk", true);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearAttack1.sqc"), ANIMATION_PATH, "Attack1", true);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearAttack2.sqc"), ANIMATION_PATH, "Attack2", true);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearDie.sqc"), ANIMATION_PATH, "Die", false);

	m_Sprite->SetRelativeScale(500.f, 500.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 150, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->SetExtent(93.f, 61.f);

	m_AttackBody->SetExtent(404.f, 240.f);

	m_Sensor->SetExtent(150.f, 30.5f);

	m_Anim->SetAnimFlip(true);

	m_Speed = 200.f;

	SetGravityAccel(30.f);
	SetPhysicsSimulate(false);
	SetJumpVelocity(40.f);
	SetSideWallCheck(false);

	SetSize(m_Body->GetInfo().Length);

	SetCharacterInfo("Taurospear");

	return true;
}

void CTaurospear::Update(float DeltaTime)
{
	CMonsterManager::Update(DeltaTime);

	if (CClientManager::GetInst()->GetFade())
	{
		return;
	}
}

void CTaurospear::PostUpdate(float DeltaTime)
{
	CMonsterManager::PostUpdate(DeltaTime);

	if (CClientManager::GetInst()->GetFade())
	{
		return;
	}
}

CTaurospear* CTaurospear::Clone()
{
	return new CTaurospear(*this);
}

void CTaurospear::AIIdle(float DeltaTime)
{
	CMonsterManager::AIIdle(DeltaTime);

	m_Anim->ChangeAnimation("Idle");
}

void CTaurospear::AIMove(float DeltaTime)
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

void CTaurospear::AITrace(float DeltaTime)
{
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

void CTaurospear::AIAttack(float DeltaTime)
{
	CMonsterManager::AIAttack(DeltaTime);

	m_Anim->ChangeAnimation("Attack");
}

void CTaurospear::AIDeath(float DeltaTime)
{
	CMonsterManager::AIDeath(DeltaTime);
}

void CTaurospear::CollisionCallbackBegin(const CollisionResult& result)
{
	CMonsterManager::CollisionCallbackBegin(result);
}

void CTaurospear::CollisionCallbackEnd(const CollisionResult& result)
{
}

void CTaurospear::AttackBegin(const CollisionResult& result)
{
	CMonsterManager::AttackBegin(result);
}

void CTaurospear::AttackEnd(const CollisionResult& result)
{
}

void CTaurospear::AnimationFinish()
{
	CMonsterManager::AnimationFinish();

	m_Anim->SetAnimFlip(m_Flip);
}
