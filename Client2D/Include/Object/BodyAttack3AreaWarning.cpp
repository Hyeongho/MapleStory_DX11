#include "BodyAttack3AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"
#include "Player2D.h"
#include "BodyAttack3Hit.h"

CBodyAttack3AreaWarning::CBodyAttack3AreaWarning()
{
	SetTypeID<CBodyAttack3AreaWarning>();
}

CBodyAttack3AreaWarning::CBodyAttack3AreaWarning(const CBodyAttack3AreaWarning& obj) : CGameObject(obj)
{
}

CBodyAttack3AreaWarning::~CBodyAttack3AreaWarning()
{
}

void CBodyAttack3AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

void CBodyAttack3AreaWarning::Start()
{
	CGameObject::Start();

	m_Body->Enable(false);
	Enable(false);
}

bool CBodyAttack3AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("CBodyAttack3AreaWarning");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Sprite->SetLayerName("Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->AddChild(m_Body);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();
	m_Anim = m_Sprite->GetAnimationInstance();
	m_Anim->AddAnimation(TEXT("Monster/Balrog/Body/Attack3AreaWarning.sqc"), ANIMATION_PATH, "Attack3AreaWarning", true, 2.52f);
	//Anim->AddAnimation("Attack3AreaWarning", "Attack3AreaWarning", false, 2.52f);

	m_Anim->SetEndFunction("Attack3AreaWarning", this, &CBodyAttack3AreaWarning::AnimationFinish);

	m_Anim->AddNotify("Attack3AreaWarning", "Attack3AreaWarning", 17, this, &CBodyAttack3AreaWarning::Attack);

	m_Body->SetCollisionProfile("MonsterAttack");

	m_Body->AddCollisionCallback<CBodyAttack3AreaWarning>(Collision_State::Begin, this, &CBodyAttack3AreaWarning::OnCollisionBegin);
	m_Body->AddCollisionCallback<CBodyAttack3AreaWarning>(Collision_State::End, this, &CBodyAttack3AreaWarning::OnCollisionEnd);

	m_Body->SetExtent(76.f, 61.f);

	m_Body->SetOffset(76.f, 61.f, 1.f);

	m_Sprite->SetRelativeScale(160.f, 499.f, 1.f);

	return true;
}

void CBodyAttack3AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack3AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack3AreaWarning* CBodyAttack3AreaWarning::Clone()
{
	return  new CBodyAttack3AreaWarning(*this);
}

void CBodyAttack3AreaWarning::SetEnable()
{
	m_Body->Enable(true);
	Enable(true);

	m_Anim->AnimationReStart();
}

void CBodyAttack3AreaWarning::OnCollisionBegin(const CollisionResult& result)
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

void CBodyAttack3AreaWarning::OnCollisionEnd(const CollisionResult& result)
{
	m_Target = false;
}

void CBodyAttack3AreaWarning::Attack()
{
	if (m_Target)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (Player)
		{
			CBodyAttack3Hit* BodyAttack3Hit = m_Scene->CreateGameObject<CBodyAttack3Hit>("BodyAttack3Hit", "BodyAttack3Hit", Player->GetWorldPos());

			CResourceManager::GetInst()->SoundPlay("BalrogBodyCharDam3");

			Player->SetDamage(10.f);
			Player->SetHurt(true);
		}
	}
}

void CBodyAttack3AreaWarning::AnimationFinish()
{
	m_Body->Enable(false);
	Enable(false);

	//Destroy();
}
