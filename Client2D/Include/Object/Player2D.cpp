#include "Player2D.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Resource/Material/Material.h"
#include "PlayerAnimation2D.h"
#include "PhantomBlow.h"
#include "BladeFury.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "PlayerManager.h"
#include "../Widget/Fade.h"
#include "../ClientManager.h"

CPlayer2D::CPlayer2D() : m_Flip(true)
{
	SetTypeID<CPlayer2D>();

	m_SolW = false;
	m_WDistance = 0.f;
	m_Opacity = 1.f;
	m_IsMove = false;
}

CPlayer2D::CPlayer2D(const CPlayer2D& obj) : CObjectManager(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("PlayerSprite");
	m_RigidBody = (CRigidBody*)FindComponent("PlayerRigidBody");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Bottom = (CColliderBox2D*)FindComponent("Bottom");
	m_Muzzle = (CColliderBox2D*)FindComponent("Muzzle");
	m_Camera = (CCameraComponent*)FindComponent("Camera");

	m_Opacity = obj.m_Opacity;
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CObjectManager::Start();

	m_PlayerStatus = m_Scene->GetViewport()->FindWidgetWindow<CPlayerStatus>("PlayerStatus");

	m_PlayerStatus->SetHPPercent((float)m_CharacterInfo.HP / m_CharacterInfo.MaxHP);
	m_PlayerStatus->SetMPPercent((float)m_CharacterInfo.MP / m_CharacterInfo.MaxMP);
}

bool CPlayer2D::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("PlayerSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Bottom = CreateComponent<CColliderBox2D>("Bottom");
	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");
	m_Camera = CreateComponent<CCameraComponent>("Camera");

	m_Muzzle->SetLayerName("Particle");

	SetRootComponent(m_Sprite);
	//m_Sprite->AddChild(m_RigidBody);
	m_Sprite->AddChild(m_Camera);
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Muzzle);
	m_Sprite->AddChild(m_Bottom);

	m_Sprite->SetTransparency(true);
	m_Sprite->SetLayerName("Player");

	//m_Sprite->CreateAnimationInstance<CPlayerAnimation2D>();

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	//m_Camera->OnViewportCenter();

	m_Body->SetCollisionProfile("Player");
	m_Bottom->SetCollisionProfile("PlayerBottom");

	m_Sprite->SetRelativeScale(250.f, 250.f, 1.f);
	//m_Sprite->SetRelativePos(100.f, 600.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_RigidBody = CreateComponent<CRigidBody>("PlayerRigidBody");

	if (CPlayerManager::GetInst()->GetGender() == Gender::Male)
	{
		Anim->AddAnimation(TEXT("M/PlayerIdle.sqc"), ANIMATION_PATH, "Idle", true);
		Anim->AddAnimation(TEXT("M/PlayerWalk.sqc"), ANIMATION_PATH, "Walk", true);
		Anim->AddAnimation(TEXT("M/PlayerJump.sqc"), ANIMATION_PATH, "Jump", true);
		Anim->AddAnimation(TEXT("M/PlayerDie.sqc"), ANIMATION_PATH, "Die", true);
		Anim->AddAnimation(TEXT("M/PlayerSwingD1.sqc"), ANIMATION_PATH, "SwingD1", true);
		Anim->AddAnimation(TEXT("M/PlayerSwingD2.sqc"), ANIMATION_PATH, "SwingD2", true);
		Anim->AddAnimation(TEXT("M/PlayerStabD1.sqc"), ANIMATION_PATH, "StabD1", true);
		Anim->AddAnimation(TEXT("M/PlayerPhantomBlow.sqc"), ANIMATION_PATH, "PhantomBlow", false);
		Anim->AddAnimation(TEXT("M/PlayerBladeFury.sqc"), ANIMATION_PATH, "BladeFury", false, 0.54f);

		m_Body->SetExtent(35.5f, 35.f);
		m_Body->SetOffset(0.f, 0.f, 0.f);

		m_Bottom->SetExtent(5.f, 1.f);
		m_Bottom->SetOffset(-5.f, -35.f, 0.f);

		m_Muzzle->SetRelativePos(0.f, 0.f, 10.f);
	}

	else if (CPlayerManager::GetInst()->GetGender() == Gender::Female)
	{
		Anim->AddAnimation(TEXT("F/PlayerIdle.sqc"), ANIMATION_PATH, "Idle", true);
		Anim->AddAnimation(TEXT("F/PlayerWalk.sqc"), ANIMATION_PATH, "Walk", true);
		Anim->AddAnimation(TEXT("F/PlayerJump.sqc"), ANIMATION_PATH, "Jump", true);
		Anim->AddAnimation(TEXT("F/PlayerDie.sqc"), ANIMATION_PATH, "Die", true);
		Anim->AddAnimation(TEXT("F/PlayerSwingD1.sqc"), ANIMATION_PATH, "SwingD1", true);
		Anim->AddAnimation(TEXT("F/PlayerSwingD2.sqc"), ANIMATION_PATH, "SwingD2", true);
		Anim->AddAnimation(TEXT("F/PlayerStabD1.sqc"), ANIMATION_PATH, "StabD1", true);
		Anim->AddAnimation(TEXT("F/PlayerPhantomBlow.sqc"), ANIMATION_PATH, "PhantomBlow", false);
		Anim->AddAnimation(TEXT("F/PlayerBladeFury.sqc"), ANIMATION_PATH, "BladeFury", false, 0.54f);

		m_Body->SetExtent(35.5f, 35.f);
		m_Body->SetOffset(0.f, 0.f, 0.f);

		m_Bottom->SetExtent(5.f, 1.f);
		m_Bottom->SetOffset(-5.f, -35.f, 0.f);

		m_Muzzle->SetRelativePos(0.f, 0.f, 10.f);
	}

	Anim->AddNotify<CPlayer2D>("PhantomBlow", "Destroy", 9, this, &CPlayer2D::AnimationFinish);
	Anim->AddNotify<CPlayer2D>("BladeFury", "Destroy", 9, this, &CPlayer2D::AnimationFinish);

	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveLeft", KeyState_Push, this, &CPlayer2D::MoveLeft);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveRight", KeyState_Push, this, &CPlayer2D::MoveRight);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveLeft", KeyState_Up, this, &CPlayer2D::Stop);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveRight", KeyState_Up, this, &CPlayer2D::Stop);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveUp", KeyState_Down, this, &CPlayer2D::MoveUp);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Jump", KeyState_Push, this, &CPlayer2D::Jump);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("SwingD1", KeyState_Down, this, &CPlayer2D::SwingD1);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("SwingD2", KeyState_Down, this, &CPlayer2D::SwingD2);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("StabD1", KeyState_Down, this, &CPlayer2D::StabD1);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("PhantomBlow", KeyState_Down, this, &CPlayer2D::PhantomBlow);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("JumpPhantomBlow", KeyState_Down, this, &CPlayer2D::JumpPhantomBlow);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("BladeFury", KeyState_Down, this, &CPlayer2D::BladeFury);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("JumpBladeFury", KeyState_Down, this, &CPlayer2D::JumpBladeFury);

	m_Bottom->AddCollisionCallback<CPlayer2D>(Collision_State::Begin, this, &CPlayer2D::CollisionCallback);

	m_IsGround = false;

	SetGravityAccel(15.f);
	SetPhysicsSimulate(true);
	SetJumpVelocity(40.f);
	SetSideWallCheck(true);

	m_State = EPlayer_State::Idle;

	SetCharacterInfo("DuelBlade");

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CObjectManager::Update(DeltaTime);

	m_PlayerStatus->SetHPPercent((float)m_CharacterInfo.HP / m_CharacterInfo.MaxHP);
	m_PlayerStatus->SetMPPercent((float)m_CharacterInfo.MP / m_CharacterInfo.MaxMP);

	Vector3 Range = GetRange();

	Vector3 Pos = GetRelativePos();

	Box2DInfo Info = m_Body->GetInfo();

	if (Pos.x - (Info.Length.x) < m_StartRange.x)
	{
		//Pos.x = (Info.Length.x);
		Pos.x = m_StartRange.x + Info.Length.x;
	}

	if (Info.Length.x + Pos.x > m_EndRange.x)
	{
		Pos.x = m_EndRange.x - Info.Length.x;
	}

	SetRelativePos(Pos);

	if (m_Flip)
	{
		m_Bottom->SetOffset(-5.f, -35.f, 0.f);
	}

	else
	{
		m_Bottom->SetOffset(5.f, -35.f, 0.f);
	}

	CGameObject* Obj = m_Scene->FindObject("PhantomBlowEffect");

	if (Obj)
	{
		Obj->SetRelativePos(m_Muzzle->GetWorldPos());
	}

	Obj = m_Scene->FindObject("BladeFury");

	if (Obj)
	{
		Obj->SetRelativePos(m_Muzzle->GetWorldPos());
	}
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CObjectManager::PostUpdate(DeltaTime);

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	switch (m_State)
	{
	case EPlayer_State::Idle:
		if (!Anim->CheckCurrentAnimation("Idle") && m_IsGround)
		{
			Anim->ChangeAnimation("Idle");
		}

		break;

	case EPlayer_State::Walk:
		if (m_IsGround)
		{
			if (!m_IsMove)
			{
				m_State = EPlayer_State::Idle;
			}

			else
			{
				if (Anim->CheckCurrentAnimation("Jump"))
				{
					m_State = EPlayer_State::Idle;
				}
			}
		}

		break;

	case EPlayer_State::Jump:
		break;
	case EPlayer_State::Rope:
		break;
	case EPlayer_State::Ladder:
		break;
	case EPlayer_State::Attack:
		break;
	case EPlayer_State::PhantomBlow:
		break;
	case EPlayer_State::BladeFury:
		break;
	case EPlayer_State::Die:
		break;
	default:
		break;
	}
}

CPlayer2D* CPlayer2D::Clone()
{
	return new CPlayer2D(*this);
}

void CPlayer2D::MoveLeft(float DeltaTime)
{
	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (m_State == EPlayer_State::PhantomBlow || m_State == EPlayer_State::BladeFury)
	{
		return;
	}

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->SetAnimFlip(false);

	m_Flip = false;

	if (m_Jump)
	{
		return;
	}

	Anim->ChangeAnimation("Walk");

	m_State = EPlayer_State::Walk;

	m_IsMove = true;

	m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * -300.f * DeltaTime);
}

void CPlayer2D::MoveRight(float DeltaTime)
{
	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (m_State == EPlayer_State::PhantomBlow || m_State == EPlayer_State::BladeFury)
	{
		return;
	}

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->SetAnimFlip(true);

	m_Flip = true;

	if (m_Jump)
	{
		return;
	}

	Anim->ChangeAnimation("Walk");

	m_State = EPlayer_State::Walk;

	m_IsMove = true;

	//m_Sprite->AddForce(Vector3(100.f, 0.f, 0.f));
	//m_RigidBody->AddForce(Vector3(100.f, 0.f, 0.f));

	m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * 300.f * DeltaTime);
}

void CPlayer2D::MoveUp(float DeltaTime)
{
	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (CPlayerManager::GetInst()->GetTagPotal())
	{
		if (m_State != EPlayer_State::Idle)
		{
			m_State = EPlayer_State::Idle;
		}

		CClientManager::GetInst()->SetFade(true);
	
		return;
	}

	if (m_State == EPlayer_State::PhantomBlow || m_State == EPlayer_State::BladeFury)
	{
		return;
	}
}

void CPlayer2D::Stop(float DeltaTime)
{
	m_IsMove = false;
}

void CPlayer2D::Jump(float DeltaTime)
{
	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (m_State == EPlayer_State::PhantomBlow || m_State == EPlayer_State::BladeFury)
	{
		return;
	}

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->ChangeAnimation("Jump");

	CResourceManager::GetInst()->SoundPlay("Jump");

	CObjectManager::Jump(Anim->GetAnimFlip());
}

void CPlayer2D::SwingD1(float DeltaTime)
{
}

void CPlayer2D::SwingD2(float DeltaTime)
{
}

void CPlayer2D::StabD1(float DeltaTime)
{
}

void CPlayer2D::PhantomBlow(float DeltaTime)
{
	if (CInput::GetInst()->GetAltDown())
	{
		return;
	}

	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (m_State == EPlayer_State::PhantomBlow || m_State == EPlayer_State::BladeFury)
	{
		return;
	}

	CPlayerManager::GetInst()->SetPlayerAttack(Player_Attack::Attack_Start);

	m_State = EPlayer_State::PhantomBlow;

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->ChangeAnimation("PhantomBlow");

	CPhantomBlow* PhantomBlow = m_Scene->CreateGameObject<CPhantomBlow>("PhantomBlowEffect");

	CResourceManager::GetInst()->SoundPlay("PhantomBlow");

	PhantomBlow->SetWorldPos(m_Muzzle->GetWorldPos());
}

void CPlayer2D::JumpPhantomBlow(float DeltaTime)
{
	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (m_State == EPlayer_State::PhantomBlow || m_State == EPlayer_State::BladeFury)
	{
		return;
	}

	CPlayerManager::GetInst()->SetPlayerAttack(Player_Attack::Attack_Start);

	m_State = EPlayer_State::PhantomBlow;

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->ChangeAnimation("PhantomBlow");

	CPhantomBlow* PhantomBlow = m_Scene->CreateGameObject<CPhantomBlow>("PhantomBlowEffect");

	CResourceManager::GetInst()->SoundPlay("PhantomBlow");

	PhantomBlow->SetWorldPos(m_Muzzle->GetWorldPos());
}

void CPlayer2D::BladeFury(float DeltaTime)
{
	if (CInput::GetInst()->GetAltDown())
	{
		return;
	}

	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (m_State == EPlayer_State::BladeFury || m_State == EPlayer_State::PhantomBlow)
	{
		return;
	}

	CPlayerManager::GetInst()->SetPlayerAttack(Player_Attack::Attack_Start);

	m_State = EPlayer_State::BladeFury;

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->ChangeAnimation("BladeFury");

	CBladeFury* BladeFury = m_Scene->CreateGameObject<CBladeFury>("BladeFury");

	CResourceManager::GetInst()->SoundPlay("BladeFury");

	BladeFury->SetWorldPos(m_Muzzle->GetWorldPos());
}

void CPlayer2D::JumpBladeFury(float DeltaTime)
{
	if (CClientManager::GetInst()->GetFadeState() != EFade_State::Normal)
	{
		return;
	}

	if (m_State == EPlayer_State::BladeFury || m_State == EPlayer_State::PhantomBlow)
	{
		return;
	}

	CPlayerManager::GetInst()->SetPlayerAttack(Player_Attack::Attack_Start);

	m_State = EPlayer_State::BladeFury;

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->ChangeAnimation("BladeFury");

	CBladeFury* BladeFury = m_Scene->CreateGameObject<CBladeFury>("BladeFury");

	CResourceManager::GetInst()->SoundPlay("BladeFury");

	BladeFury->SetWorldPos(m_Muzzle->GetWorldPos());
}

void CPlayer2D::CollisionCallback(const CollisionResult& result)
{
	result.Src->GetCollisionProfile();

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Floor)
	{
		m_IsGround = true;
		m_Jump = false;
	}
}

void CPlayer2D::AnimationFinish()
{
	m_State = EPlayer_State::Idle;
}
