#include "RightAttack1AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"
#include "Player2D.h"
#include "RightAttack1Hit.h"

CRightAttack1AreaWarning::CRightAttack1AreaWarning()
{
	SetTypeID<CRightAttack1AreaWarning>();
}

CRightAttack1AreaWarning::CRightAttack1AreaWarning(const CRightAttack1AreaWarning& obj) : CGameObject(obj)
{
}

CRightAttack1AreaWarning::~CRightAttack1AreaWarning()
{
}

void CRightAttack1AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

void CRightAttack1AreaWarning::Start()
{
	CGameObject::Start();

	m_Body->Enable(false);
	Enable(false);
}

bool CRightAttack1AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("RightAttack1AreaWarning");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Balrog/Right/RightAttack1AreaWarning.sqc"), ANIMATION_PATH, "RightAttack1AreaWarning", true, 0.5f);

	m_Anim->AddNotify("RightAttack1AreaWarning", "RightAttack1AreaWarning", 1, this, &CRightAttack1AreaWarning::Attack);

	m_Anim->SetEndFunction("RightAttack1AreaWarning", this, &CRightAttack1AreaWarning::AnimationFinish);

	m_Sprite->SetRelativeScale(142.f, 676.f, 1.f);

	m_Body->SetCollisionProfile("MonsterAttack");

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CRightAttack1AreaWarning::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CRightAttack1AreaWarning::OnCollisionEnd);

	m_Body->SetExtent(71.f, 338.f);
	m_Body->SetOffset(71.f, 338.f, 1.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CRightAttack1AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRightAttack1AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRightAttack1AreaWarning* CRightAttack1AreaWarning::Clone()
{
	return  new CRightAttack1AreaWarning(*this);
}

void CRightAttack1AreaWarning::SetEnable()
{
	m_Body->Enable(true);
	Enable(true);

	m_Anim->AnimationReStart();
}

void CRightAttack1AreaWarning::OnCollisionBegin(const CollisionResult& result)
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

void CRightAttack1AreaWarning::OnCollisionEnd(const CollisionResult& result)
{
	m_Target = false;
}

void CRightAttack1AreaWarning::Attack()
{
	if (m_Target)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (Player && !Player->GetHurt())
		{
			CRightAttack1Hit* RightAttack1Hit = m_Scene->CreateGameObject<CRightAttack1Hit>("RightAttack1Hit", "RightAttack1Hit", Player->GetWorldPos());

			CResourceManager::GetInst()->SoundPlay("BalrogRightCharDam1");

			Player->SetDamage(10.f);

			Player->SetHurt(true);
		}
	}
}

void CRightAttack1AreaWarning::AnimationFinish()
{
	m_Body->Enable(false);
	Enable(false);

	if (m_Target)
	{
		m_Target = false;
	}
}
