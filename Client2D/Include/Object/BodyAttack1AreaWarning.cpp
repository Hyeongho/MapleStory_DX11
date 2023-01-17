#include "BodyAttack1AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Player2D.h"
#include "Balrog.h"
#include "BodyAttack1Hit.h"

CBodyAttack1AreaWarning::CBodyAttack1AreaWarning() : m_Target(false)
{
	SetTypeID<CBodyAttack1AreaWarning>();
}

CBodyAttack1AreaWarning::CBodyAttack1AreaWarning(const CBodyAttack1AreaWarning& obj) : CGameObject(obj)
{
}

CBodyAttack1AreaWarning::~CBodyAttack1AreaWarning()
{
}

void CBodyAttack1AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

void CBodyAttack1AreaWarning::Start()
{
	CGameObject::Start();

	m_Body->Enable(false);
	Enable(false);
}

bool CBodyAttack1AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Attack1AreaWarning");

	m_Sprite->SetRelativeScale(547.f, 678.f, 1.f);

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Body->SetCollisionProfile("MonsterAttack");

	//m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/Balrog/Body/Attack1AreaWarning.sqc"), ANIMATION_PATH, "Attack1AreaWarning", true, 1.68f);
	m_Anim->SetEndFunction("Attack1AreaWarning", this, &CBodyAttack1AreaWarning::AnimationFinish);

	m_Anim->AddNotify("Attack1AreaWarning", "Attack1AreaWarning", 8, this, &CBodyAttack1AreaWarning::Attack);

	m_Body->AddCollisionCallback<CBodyAttack1AreaWarning>(Collision_State::Begin, this, &CBodyAttack1AreaWarning::OnCollisionBegin);
	m_Body->AddCollisionCallback<CBodyAttack1AreaWarning>(Collision_State::End, this, &CBodyAttack1AreaWarning::OnCollisionEnd);

	m_Body->SetExtent(273.5f, 150.f);
	m_Body->SetOffset(0.f, 0.f, 0.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CBodyAttack1AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack1AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack1AreaWarning* CBodyAttack1AreaWarning::Clone()
{
	return  new CBodyAttack1AreaWarning(*this);
}

void CBodyAttack1AreaWarning::SetEnable()
{
	m_Body->Enable(true);
	Enable(true);

	//m_Body->SetRelativePos(GetRelativePos());
	m_Body->SetOffset(273.5f, 150.f, 1.f);

	m_Anim->AnimationReStart();
}

void CBodyAttack1AreaWarning::OnCollisionBegin(const CollisionResult& result)
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

void CBodyAttack1AreaWarning::OnCollisionEnd(const CollisionResult& result)
{
	m_Target = false;
}

void CBodyAttack1AreaWarning::Attack()
{
	if (m_Target)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (Player && !Player->GetHurt())
		{
			CBodyAttack1Hit* BodyAttack1Hit = m_Scene->CreateGameObject<CBodyAttack1Hit>("BodyAttack1Hit", "BodyAttack1Hit", Player->GetWorldPos());

			CResourceManager::GetInst()->SoundPlay("BalrogBodyCharDam1");

			Player->SetDamage(10.f);
			Player->SetHurt(true);
		}
	}
}

void CBodyAttack1AreaWarning::AnimationFinish()
{
	m_Body->Enable(false);
	Enable(false);

	//Destroy();
}
