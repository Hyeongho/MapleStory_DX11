#include "ShadowDualBlade.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"

CShadowDualBlade::CShadowDualBlade()
{
	SetTypeID<CShadowDualBlade>();

	m_SolW = false;
	m_WDistance = 0.f;
	m_Opacity = 1.f;
}

CShadowDualBlade::CShadowDualBlade(const CShadowDualBlade& obj) : CMonsterManager(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("ShadowDualBlade");

	m_Body = (CColliderBox2D*)FindComponent("Body");

	m_Sensor = (CColliderBox2D*)FindComponent("Sensor");

	m_AttackBody = (CColliderBox2D*)FindComponent("AttackBody");

	m_Opacity = obj.m_Opacity;
}

CShadowDualBlade::~CShadowDualBlade()
{
}

void CShadowDualBlade::Start()
{
	CMonsterManager::Start();
}

bool CShadowDualBlade::Init()
{
	CMonsterManager::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("ShadowDualBlade");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sensor = CreateComponent<CColliderBox2D>("Sensor");
	m_AttackBody = CreateComponent<CColliderBox2D>("AttackBody");
	m_AttackRange = CreateComponent<CColliderBox2D>("AttackRange");
	m_Muzzle = CreateComponent<CSceneComponent>("SDBMuzzle");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	m_Sensor->SetCollisionProfile("Monster");
	m_AttackBody->SetCollisionProfile("MonsterAttack");
	m_AttackRange->SetCollisionProfile("MonsterAttack");
	//m_Body->AddCollisionCallback<CShadowDualBlade>(Collision_State::Begin, this, &CShadowDualBlade::CollisionCallback);

	m_Sensor->AddCollisionCallback<CShadowDualBlade>(Collision_State::Begin, this, &CMonsterManager::CollisionCallbackBegin);
	m_Sensor->AddCollisionCallback<CShadowDualBlade>(Collision_State::End, this, &CShadowDualBlade::CollisionCallbackEnd);

	m_AttackBody->AddCollisionCallback<CShadowDualBlade>(Collision_State::Begin, this, &CMonsterManager::AttackBegin);
	m_AttackBody->AddCollisionCallback<CShadowDualBlade>(Collision_State::End, this, &CShadowDualBlade::AttackEnd);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Sensor);
	m_Sprite->AddChild(m_AttackBody);
	
	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Shadow Dual Blade/Idle.sqc"), ANIMATION_PATH, "Idle", true);
	m_Anim->AddAnimation(TEXT("Monster/Shadow Dual Blade/Walk.sqc"), ANIMATION_PATH, "Walk", true);
	m_Anim->AddAnimation(TEXT("Monster/Shadow Dual Blade/Attack.sqc"), ANIMATION_PATH, "Attack", true);
	m_Anim->AddAnimation(TEXT("Monster/Shadow Dual Blade/Die.sqc"), ANIMATION_PATH, "Die", false);

	m_Anim->AddNotify<CShadowDualBlade>("Attack", "Attack", 6, this, &CShadowDualBlade::AnimationFinish);
	m_Anim->AddNotify<CShadowDualBlade>("Die", "Die", 14, this, &CShadowDualBlade::AnimationFinish);

	m_Sprite->SetRelativeScale(300.f, 150.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 150, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	
	m_Body->SetExtent(28.5f, 30.5f);

	SetSize(m_Body->GetInfo().Length);

	m_AttackBody->SetExtent(75.f, 30.f);

	m_Sensor->SetExtent(150.f, 30.5f);

	m_Anim->SetAnimFlip(true);

	m_Speed = 200.f;

	SetGravityAccel(30.f);
	SetPhysicsSimulate(false);
	SetJumpVelocity(40.f);
	SetSideWallCheck(false);

	m_RandActive = (float)(rand() % 2);

	SetCharacterInfo("ShadowDualBlade");

	return true;
}

void CShadowDualBlade::Update(float DeltaTime)
{
	CMonsterManager::Update(DeltaTime);

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}
}

void CShadowDualBlade::PostUpdate(float DeltaTime)
{
	CMonsterManager::PostUpdate(DeltaTime);

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}
}

CShadowDualBlade* CShadowDualBlade::Clone()
{
	return new CShadowDualBlade(*this);
}

void CShadowDualBlade::AIIdle(float DeltaTime)
{
	CMonsterManager::AIIdle(DeltaTime);

	m_Anim->ChangeAnimation("Idle");
}

void CShadowDualBlade::AIMove(float DeltaTime)
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

void CShadowDualBlade::AITrace(float DeltaTime)
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

void CShadowDualBlade::AIAttack(float DeltaTime)
{
	CMonsterManager::AIAttack(DeltaTime);

	if (m_Anim->CheckCurrentAnimation("Attack"))
	{
		return;
	}

	m_Anim->ChangeAnimation("Attack");
}

void CShadowDualBlade::AIDeath(float DeltaTime)
{
	CMonsterManager::AIDeath(DeltaTime);

	m_Body->Destroy();
	m_Sensor->Destroy();
	m_AttackBody->Destroy();
	m_AttackRange->Destroy();

	m_Anim->ChangeAnimation("Die");

	//Destroy();
}

void CShadowDualBlade::CreateAttackRange()
{
	if (m_Flip)
	{

	}

	else
	{

	}
}

void CShadowDualBlade::CollisionCallbackBegin(const CollisionResult& result)
{
	CMonsterManager::CollisionCallbackBegin(result);
}

void CShadowDualBlade::CollisionCallbackEnd(const CollisionResult& result)
{
	//CMonsterManager::CollisionCallbackEnd(result);

	result.Src->GetCollisionProfile();

	if (!result.Dest->GetCollisionProfile() || (result.Dest->GetColliderType() != Collider_Type::Box2D))
	{
		return;
	}

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		m_Trace = false;

		m_State = EMonster_State::Move;
	}
}

void CShadowDualBlade::AttackBegin(const CollisionResult& result)
{
	CMonsterManager::AttackBegin(result);
}

void CShadowDualBlade::AttackEnd(const CollisionResult& result)
{
	//CMonsterManager::AttackEnd(result);

	result.Src->GetCollisionProfile();
	result.Dest->GetCollisionProfile();

	if (!result.Dest->GetCollisionProfile() || (result.Dest->GetColliderType() != Collider_Type::Box2D))
	{
		return;
	}

	if (result.Dest->GetCollisionProfile()->Name == "Player")
	{
		m_Attack = false;
	}
}

void CShadowDualBlade::AnimationFinish()
{
	CMonsterManager::AnimationFinish();

	if (m_Anim->CheckCurrentAnimation("Die"))
	{
		Destroy();
		return;
	}

	m_Anim->SetAnimFlip(m_Flip);
}