#include "LeftAttack1AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"
#include "Player2D.h"
#include "LeftAttack1Hit.h"

CLeftAttack1AreaWarning::CLeftAttack1AreaWarning()
{
	SetTypeID<CLeftAttack1AreaWarning>();
}

CLeftAttack1AreaWarning::CLeftAttack1AreaWarning(const CLeftAttack1AreaWarning& obj) : CGameObject(obj)
{
}

CLeftAttack1AreaWarning::~CLeftAttack1AreaWarning()
{
}

void CLeftAttack1AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

void CLeftAttack1AreaWarning::Start()
{
	CGameObject::Start();

	m_Body->Enable(false);
	Enable(false);
}

bool CLeftAttack1AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("LeftAttack1AreaWarning");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Balrog/Left/LeftAttack1AreaWarning.sqc"), ANIMATION_PATH, "LeftAttack1AreaWarning", true, 1.68f);

	m_Anim->AddNotify("LeftAttack1AreaWarning", "LeftAttack1AreaWarning", 6, this, &CLeftAttack1AreaWarning::Attack);

	m_Anim->SetEndFunction("LeftAttack1AreaWarning", this, &CLeftAttack1AreaWarning::AnimationFinish);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CLeftAttack1AreaWarning::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CLeftAttack1AreaWarning::OnCollisionEnd);

	m_Body->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetRelativeScale(147.f, 139.f, 1.f);

	m_Body->SetExtent(73.5f, 69.5f);
	m_Body->SetOffset(73.5f, 69.5f, 1.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CLeftAttack1AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CLeftAttack1AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CLeftAttack1AreaWarning* CLeftAttack1AreaWarning::Clone()
{
	return  new CLeftAttack1AreaWarning(*this);
}

void CLeftAttack1AreaWarning::SetEnable()
{
	m_Body->Enable(true);
	Enable(true);

	m_Body->SetOffset(73.5f, 69.5f, 1.f);

	m_Anim->AnimationReStart();
}

void CLeftAttack1AreaWarning::OnCollisionBegin(const CollisionResult& result)
{
	if (!result.Dest->GetCollisionProfile())
	{
		return;
	}

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (!Player)
		{
			return;
		}

		m_Target = true;
	}
}

void CLeftAttack1AreaWarning::OnCollisionEnd(const CollisionResult& result)
{
	m_Target = false;
}

void CLeftAttack1AreaWarning::Attack()
{
	if (m_Target)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (Player && !Player->GetHurt())
		{
			CLeftAttack1Hit* LeftAttack1Hit = m_Scene->CreateGameObject<CLeftAttack1Hit>("LeftAttack1Hit", "LeftAttack1Hit", Player->GetWorldPos());

			CResourceManager::GetInst()->SoundPlay("BalrogLeftCharDam1");

			Player->SetDamage(10.f);

			Player->SetHurt(true);
		}
	}
}

void CLeftAttack1AreaWarning::AnimationFinish()
{
	m_Body->Enable(false);
	Enable(false);

	if (m_Target)
	{
		m_Target = false;
	}
}
