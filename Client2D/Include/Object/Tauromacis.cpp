#include "Tauromacis.h"
#include "TauromacisHitEffect.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Resource/Sound/SoundManager.h"

CTauromacis::CTauromacis()
{
	SetTypeID<CTauromacis>();

	m_SolW = false;
	m_WDistance = 0.f;
}

CTauromacis::CTauromacis(const CTauromacis& obj) : CMonsterManager(obj)
{
	m_Sprite = dynamic_cast<CSpriteComponent*>(FindComponent("Tauromacis"));

	m_Body = dynamic_cast<CColliderBox2D*>(FindComponent("Body"));

	m_Sensor = dynamic_cast<CColliderBox2D*>(FindComponent("Sensor"));

	m_AttackBody = dynamic_cast<CColliderBox2D*>(FindComponent("AttackBody"));

	m_Opacity = obj.m_Opacity;
}

CTauromacis::~CTauromacis()
{
}

void CTauromacis::Start()
{
	CMonsterManager::Start();
}

bool CTauromacis::Init()
{
	CMonsterManager::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Tauromacis");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	//m_Sensor = CreateComponent<CColliderBox2D>("Sensor");
	m_AttackBody = CreateComponent<CColliderBox2D>("AttackBody");
	m_AttackRange = CreateComponent<CColliderBox2D>("AttackRange");
	m_Muzzle = CreateComponent<CSceneComponent>("TauromacisMuzzle");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	//m_Sensor->SetCollisionProfile("Monster");
	m_AttackBody->SetCollisionProfile("MonsterAttack");
	m_AttackRange->SetCollisionProfile("MonsterAttack");

	/*m_Sensor->AddCollisionCallback<CTauromacis>(Collision_State::Begin, this, &CMonsterManager::CollisionCallbackBegin);
	m_Sensor->AddCollisionCallback<CTauromacis>(Collision_State::End, this, &CTauromacis::CollisionCallbackEnd);*/

	m_AttackBody->AddCollisionCallback<CTauromacis>(Collision_State::Begin, this, &CMonsterManager::AttackBegin);
	m_AttackBody->AddCollisionCallback<CTauromacis>(Collision_State::End, this, &CTauromacis::AttackEnd);

	m_Sprite->AddChild(m_Body);
	//m_Sprite->AddChild(m_Sensor);
	m_Sprite->AddChild(m_AttackBody);
	m_Sprite->AddChild(m_AttackRange);
	m_Sprite->AddChild(m_Muzzle);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Tauromacis/TauromacisIdle.sqc"), ANIMATION_PATH, "Idle", true);
	m_Anim->AddAnimation(TEXT("Monster/Tauromacis/TauromacisMove.sqc"), ANIMATION_PATH, "Walk", true);
	m_Anim->AddAnimation(TEXT("Monster/Tauromacis/TauromacisAttack.sqc"), ANIMATION_PATH, "Attack", true);
	m_Anim->AddAnimation(TEXT("Monster/Tauromacis/TauromacisDie.sqc"), ANIMATION_PATH, "Die", false);

	m_Anim->AddNotify<CTauromacis>("Attack", "PlaySound", 0, this, &CTauromacis::PlayAttackSound);
	m_Anim->AddNotify<CTauromacis>("Die", "PlaySound", 0, this, &CTauromacis::PlayDieSound);
	m_Anim->AddNotify<CTauromacis>("Attack", "PlayerHit", 4, this, &CTauromacis::Attack1Damage);
	//m_Anim->AddNotify<CTauromacis>("Attack", "Attack", 6, this, &CTauromacis::AnimationFinish);
	m_Anim->SetEndFunction<CTauromacis>("Attack", this, &CTauromacis::AnimationFinish);
	m_Anim->SetEndFunction<CTauromacis>("Die", this, &CTauromacis::AnimationFinish);

	m_Sprite->SetRelativeScale(500.f, 500.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 150, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->SetExtent(81.f, 60.f);

	m_AttackBody->SetExtent(404.f, 240.f);

	//m_Sensor->SetExtent(150.f, 30.5f);

	m_Anim->SetAnimFlip(true);

	m_Speed = 200.f;

	SetGravityAccel(30.f);
	SetPhysicsSimulate(false);
	SetJumpVelocity(40.f);
	SetSideWallCheck(false);

	SetSize(m_Body->GetInfo().Length);

	SetCharacterInfo("Tauromacis");

	return true;
}

void CTauromacis::Update(float DeltaTime)
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

void CTauromacis::PostUpdate(float DeltaTime)
{
	CMonsterManager::PostUpdate(DeltaTime);

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}
}

CTauromacis* CTauromacis::Clone()
{
	return new CTauromacis(*this);
}

void CTauromacis::AIIdle(float DeltaTime)
{
	CMonsterManager::AIIdle(DeltaTime);

	m_Anim->ChangeAnimation("Idle");
}

void CTauromacis::AIMove(float DeltaTime)
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

void CTauromacis::AITrace(float DeltaTime)
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

void CTauromacis::AIAttack(float DeltaTime)
{
	CMonsterManager::AIAttack(DeltaTime);

	if (m_Anim->CheckCurrentAnimation("Attack"))
	{
		return;
	}

	m_Anim->ChangeAnimation("Attack");
}

void CTauromacis::AIDeath(float DeltaTime)
{
	CMonsterManager::AIDeath(DeltaTime);

	m_Body->Destroy();
	//m_Sensor->Destroy();
	m_AttackBody->Destroy();
	m_AttackRange->Destroy();

	m_Anim->ChangeAnimation("Die");
}

void CTauromacis::LoadSound()
{
	
}

void CTauromacis::CollisionCallbackBegin(const CollisionResult& result)
{
	CMonsterManager::CollisionCallbackBegin(result);
}

void CTauromacis::CollisionCallbackEnd(const CollisionResult& result)
{
}

void CTauromacis::AttackBegin(const CollisionResult& result)
{
	CMonsterManager::AttackBegin(result);

	m_Attack = true;
	m_Hurt = true;
}

void CTauromacis::AttackEnd(const CollisionResult& result)
{
	m_Attack = false;
}

void CTauromacis::PlayAttackSound()
{
	CResourceManager::GetInst()->SoundPlay("TaurmoacisAttack1");
}

void CTauromacis::PlayDieSound()
{
	CResourceManager::GetInst()->SoundPlay("TaurmoacisDie");
}

void CTauromacis::Attack1Damage()
{
	if (m_Hurt)
	{
		if (!m_Player->GetHurt())
		{
			CTauromacisHitEffect* TauromacisHitEffect = m_Scene->CreateGameObject<CTauromacisHitEffect>("TauromacisHitEffect", "TauromacisHitEffect", m_Player->GetWorldPos(), Vector3(250.f, 250.f, 1.f));
			TauromacisHitEffect->SetWorldPos(m_Player->GetWorldPos());

			m_Player->SetDamage(10);

			m_Player->SetHurt(true);
		}
	}
}

void CTauromacis::AnimationFinish()
{
	CMonsterManager::AnimationFinish();

	if (m_Anim->CheckCurrentAnimation("Die"))
	{
		m_IsHide = true;
		return;
	}

	m_Anim->SetAnimFlip(m_Flip);
}
