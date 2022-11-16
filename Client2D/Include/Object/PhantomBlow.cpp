#include "PhantomBlow.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Player2D.h"
#include "PlayerManager.h"
#include "DamageFont.h"
#include "MonsterManager.h"

CPhantomBlow::CPhantomBlow()
{
	SetTypeID<CPhantomBlow>();
}

CPhantomBlow::CPhantomBlow(const CPhantomBlow& obj) : CSkillManager(obj)
{
	m_Muzzle = dynamic_cast<CSceneComponent*>(FindComponent("Muzzle"));

	m_Sprite1 = dynamic_cast<CSpriteComponent*>(FindComponent("PhantomBlow1"));
	m_Sprite2 = dynamic_cast<CSpriteComponent*>(FindComponent("PhantomBlow2"));
	m_Body = dynamic_cast<CColliderBox2D*>(FindComponent("Body"));
}

CPhantomBlow::~CPhantomBlow()
{
	//Destroy();
}

void CPhantomBlow::SetCollisionProfile(const std::string& Name)
{
}

void CPhantomBlow::Start()
{
	CSkillManager::Start();
}

bool CPhantomBlow::Init()
{
	CSkillManager::Init();

	CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

	if (!Player)
	{
		return false;
	}

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Sprite1 = CreateComponent<CSpriteComponent>("PhantomBlow1");
	m_Sprite2 = CreateComponent<CSpriteComponent>("PhantomBlow2");

	m_Sprite1->SetLayerName("Effect");
	m_Sprite2->SetLayerName("Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Muzzle);

	m_Muzzle->AddChild(m_Sprite1);
	m_Muzzle->AddChild(m_Sprite2);

	m_Sprite1->SetTransparency(true);
	m_Sprite2->SetTransparency(true);

	m_Sprite1->AddChild(m_Body);

	m_Sprite1->CreateAnimationInstance<CAnimationSequence2DInstance>();
	m_Anim1 = m_Sprite1->GetAnimationInstance();
	m_Anim1->AddAnimation(TEXT("Skill/PhantomBlow/PhantomBlow.sqc"), ANIMATION_PATH, "PhantomBlow1", false);

	//m_Anim1->AddAnimation("PhantomBlow1", "PhantomBlow1", false);
	
	m_Anim1->AddNotify<CPhantomBlow>("PhantomBlow1", "Destroy", 10, this, &CPhantomBlow::AnimationFinish);

	m_Sprite2->CreateAnimationInstance<CAnimationSequence2DInstance>();
	m_Anim2 = m_Sprite2->GetAnimationInstance();
	m_Anim2->AddAnimation(TEXT("Skill/PhantomBlow/PhantomBlow0.sqc"), ANIMATION_PATH, "PhantomBlow2", false);

	//m_Anim2->AddAnimation("PhantomBlow2", "PhantomBlow2", false);

	m_Muzzle->SetPivot(0.5f, 0.5f, 0.f);

	if (Player->GetFlip())
	{
		m_Sprite1->SetRelativeScale(616.f, 310.f, 2.f);
		m_Sprite1->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite1->SetRelativePos(161.f, 35.5f, 11.f);

		m_Sprite2->SetRelativeScale(230.f, 110.f, 2.f);
		m_Sprite2->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite2->SetRelativePos(-80.f, 5.f, 11.f);

		m_Body->SetRelativePos(m_Sprite1->GetRelativePos());
		m_Body->SetExtent(154.f, 77.5f);
		m_Body->SetOffset(-154.f, -77.5f, 0.f);
	}

	else
	{
		m_Anim1->SetAnimFlip(false);
		m_Anim2->SetAnimFlip(false);

		m_Sprite1->SetRelativeScale(616.f, 310.f, 2.f);
		m_Sprite1->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite1->SetRelativePos(-161.f, 35.5f, 11.f);

		m_Sprite2->SetRelativeScale(230.f, 110.f, 2.f);
		m_Sprite2->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite2->SetRelativePos(80.f, 5.f, 11.f);

		m_Body->SetRelativePos(m_Sprite1->GetRelativePos());
		m_Body->SetExtent(154.f, 77.5f);
		m_Body->SetOffset(154.f, -77.5f, 0.f);
	}

	m_Body->AddCollisionCallback<CPhantomBlow>(Collision_State::Begin, this, &CPhantomBlow::OnCollisionBegin);
	m_Body->SetCollisionProfile("PlayerAttack");

	m_Damage = 0;

	return true;
}

void CPhantomBlow::Update(float DeltaTime)
{
	CSkillManager::Update(DeltaTime);
}

void CPhantomBlow::PostUpdate(float DeltaTime)
{
	CSkillManager::PostUpdate(DeltaTime);
}

CPhantomBlow* CPhantomBlow::Clone()
{
	return new CPhantomBlow(*this);
}

void CPhantomBlow::OnCollisionBegin(const CollisionResult& result)
{
	m_obj = (CMonsterManager*)result.Dest->GetGameObject();

	int Frame = m_Anim1->GetFrame();

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Monster)
	{
		for (int i = 0; i < 6; i++)
		{
			//result.Dest->GetGameObject()->SetDamage(10);

			m_TargetPos = m_obj->GetWorldPos();
			m_TargetSize = m_obj->GetSize();

			//m_obj->SetDamage(10);

			m_Anim1->AddNotify<CPhantomBlow>("PhantomBlow1", "PhantomBlow1", i, this, &CPhantomBlow::Attack);
		}
	}
}

void CPhantomBlow::AnimationFinish()
{
	if (m_obj)
	{
		if (m_obj->GetCharacterInfo().HP <= 0)
		{
			m_obj->SetDie(true);
		}
	}

	Destroy();
}

void CPhantomBlow::Attack()
{
	int Frame = m_Anim1->GetFrame();

	CDamageFont* DamageFont = m_Scene->CreateGameObject<CDamageFont>("DamagrFont");
	DamageFont->SetWorldPos(m_TargetPos.x - 31.f, m_TargetPos.y + (m_TargetSize.y) + (Frame * 30), 1);

	m_Damage = 10;

	DamageFont->SetDamageNumber(m_Damage);

	if (m_obj)
	{
		m_obj->SetDamage((float)m_Damage);
	}
}
