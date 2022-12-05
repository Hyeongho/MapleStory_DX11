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
	CMonsterManager::Start();
}

bool CTaurospear::Init()
{
	CMonsterManager::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Taurospear");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	//m_Sensor = CreateComponent<CColliderBox2D>("Sensor");
	m_Attack1Body = CreateComponent<CColliderBox2D>("Attack1Body");
	m_Attack2Body = CreateComponent<CColliderBox2D>("Attack2Body");
	m_AttackRange = CreateComponent<CColliderBox2D>("AttackRange");
	m_Muzzle = CreateComponent<CSceneComponent>("TauromacisMuzzle");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	//m_Sensor->SetCollisionProfile("Monster");
	m_Attack1Body->SetCollisionProfile("MonsterAttack");
	m_Attack2Body->SetCollisionProfile("MonsterAttack");
	m_AttackRange->SetCollisionProfile("MonsterAttack");

	/*m_Sensor->AddCollisionCallback<CTaurospear>(Collision_State::Begin, this, &CMonsterManager::CollisionCallbackBegin);
	m_Sensor->AddCollisionCallback<CTaurospear>(Collision_State::End, this, &CTaurospear::CollisionCallbackEnd);*/

	m_Attack1Body->AddCollisionCallback<CTaurospear>(Collision_State::Begin, this, &CTaurospear::Attack1Begin);
	m_Attack1Body->AddCollisionCallback<CTaurospear>(Collision_State::End, this, &CTaurospear::Attack1End);

	m_Attack2Body->AddCollisionCallback<CTaurospear>(Collision_State::Begin, this, &CTaurospear::Attack2Begin);
	m_Attack2Body->AddCollisionCallback<CTaurospear>(Collision_State::End, this, &CTaurospear::Attack2End);

	m_Sprite->AddChild(m_Body);
	//m_Sprite->AddChild(m_Sensor);
	m_Sprite->AddChild(m_Attack1Body);
	m_Sprite->AddChild(m_Attack2Body);
	m_Sprite->AddChild(m_AttackRange);
	m_Sprite->AddChild(m_Muzzle);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearIdle.sqc"), ANIMATION_PATH, "Idle", true);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearMove.sqc"), ANIMATION_PATH, "Walk", true);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearAttack1.sqc"), ANIMATION_PATH, "Attack1", true);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearAttack2.sqc"), ANIMATION_PATH, "Attack2", true, 1.91f);
	m_Anim->AddAnimation(TEXT("Monster/Taurospear/TaurospearDie.sqc"), ANIMATION_PATH, "Die", false);

	m_Anim->AddNotify("Attack1", "Attack1", 5, this, &CTaurospear::Attack1);
	m_Anim->AddNotify("Attack2", "Attack2", 3, this, &CTaurospear::Attack2);

	m_Anim->AddNotify<CTaurospear>("Attack1", "Attack1PlaySound", 0, this, &CTaurospear::PlayAttackSound);
	m_Anim->AddNotify<CTaurospear>("Attack2", "Attack2PlaySound", 0, this, &CTaurospear::PlayAttackSound);

	m_Anim->SetEndFunction<CTaurospear>("Attack1", this, &CTaurospear::AnimationFinish);
	m_Anim->SetEndFunction<CTaurospear>("Attack2", this, &CTaurospear::AnimationFinish);
	m_Anim->SetEndFunction<CTaurospear>("Die", this, &CTaurospear::AnimationFinish);

	m_Sprite->SetRelativeScale(500.f, 500.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 150, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->SetExtent(93.f, 61.f);

	m_Attack1Body->SetExtent(209.f, 225.f);
	m_Attack2Body->SetExtent(250.f, 60.f);

	//m_Sensor->SetExtent(150.f, 30.5f);

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

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}

	if (m_IsHide)
	{
		m_Opacity -= DeltaTime / 1.f;

		if (m_Opacity < 0.f)
		{
			Destroy();
			return;
		}

		m_Sprite->SetOpacity(m_Opacity);
	}
}

void CTaurospear::PostUpdate(float DeltaTime)
{
	CMonsterManager::PostUpdate(DeltaTime);

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
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

void CTaurospear::AIAttack(float DeltaTime)
{
	CMonsterManager::AIAttack(DeltaTime);

	if (m_Anim->CheckCurrentAnimation("Attack1") || m_Anim->CheckCurrentAnimation("Attack2"))
	{
		return;
	}

	m_Anim->SetAnimFlip(m_Flip);

	int num = (rand() % 2) + 1;

	if (num == 1)
	{
		m_Anim->ChangeAnimation("Attack1");
	}

	else
	{
		m_Anim->ChangeAnimation("Attack2");
	}
}

void CTaurospear::AIDeath(float DeltaTime)
{
	CMonsterManager::AIDeath(DeltaTime);

	m_Body->Destroy();
	//m_Sensor->Destroy();
	m_Attack1Body->Destroy();
	m_Attack2Body->Destroy();
	m_AttackRange->Destroy();

	m_Anim->ChangeAnimation("Die");
}

void CTaurospear::CollisionCallbackBegin(const CollisionResult& result)
{
	CMonsterManager::CollisionCallbackBegin(result);
}

void CTaurospear::CollisionCallbackEnd(const CollisionResult& result)
{
}

void CTaurospear::Attack1Begin(const CollisionResult& result)
{
	CMonsterManager::AttackBegin(result);

	m_Attack = true;
	m_Hurt1 = true;
}

void CTaurospear::Attack1End(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		if (m_Hurt1)
		{
			m_Hurt1 = false;
		}
	}

	m_Attack = false;
}

void CTaurospear::Attack2Begin(const CollisionResult& result)
{
	CMonsterManager::AttackBegin(result);

	m_Attack = true;
	m_Hurt2 = true;
}

void CTaurospear::Attack2End(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		if (m_Hurt2)
		{
			m_Hurt2 = false;
		}
	}

	m_Attack = false;
}

void CTaurospear::Attack1()
{
	if (m_Hurt1)
	{
		if (!m_Player->GetHurt())
		{
			m_Player->SetDamage(10);

			m_Player->SetHurt(true);
		}
	}
}

void CTaurospear::Attack2()
{
	if (m_Hurt2)
	{
		if (!m_Player->GetHurt())
		{
			m_Player->SetDamage(10);

			m_Player->SetHurt(true);
		}
	}
}

void CTaurospear::PlayAttackSound()
{
	if (m_Anim->CheckCurrentAnimation("Attack1"))
	{
		CResourceManager::GetInst()->SoundPlay("TaurospearAttack1");
	}

	else if (m_Anim->CheckCurrentAnimation("Attack2"))
	{
		CResourceManager::GetInst()->SoundPlay("TaurospearAttack2");
	}
}

void CTaurospear::AnimationFinish()
{
	if (m_Attack)
	{
		int num = (rand() % 2) + 1;

		if (num == 1)
		{
			m_Anim->ChangeAnimation("Attack1");
		}

		else
		{
			m_Anim->ChangeAnimation("Attack2");
		}
	}

	else
	{
		CMonsterManager::AnimationFinish();
	}

	if (m_Anim->CheckCurrentAnimation("Die"))
	{
		m_IsHide = true;
		return;
	}

	m_Anim->SetAnimFlip(m_Flip);
}
