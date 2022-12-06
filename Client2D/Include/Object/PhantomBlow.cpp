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
	m_Muzzle = obj.m_Muzzle;

	m_Sprite1 = obj.m_Sprite1;
	m_Sprite2 = obj.m_Sprite2;
	m_Body = obj.m_Body;
	m_Anim1 = obj.m_Anim1;
	m_Anim2 = obj.m_Anim2;

	SetRootComponent(m_Muzzle);

	m_Muzzle->AddChild(m_Sprite1);
	m_Muzzle->AddChild(m_Sprite2);

	/*m_Anim1->AnimationReStart();
	m_Anim2->AnimationReStart();*/
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

	m_Anim1->AddNotify<CPhantomBlow>("PhantomBlow1", "OnCollision", 0, this, &CPhantomBlow::OnCollision);
	m_Anim1->AddNotify<CPhantomBlow>("PhantomBlow1", "OffCollision", 1, this, &CPhantomBlow::OffCollision);

	m_Body->Enable(false);

	Enable(false);
}

bool CPhantomBlow::Init()
{
	CSkillManager::Init();

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

	//m_Anim1->AddNotify<CPhantomBlow>("PhantomBlow1", "Destroy", 10, this, &CPhantomBlow::AnimationFinish);
	m_Anim1->SetEndFunction<CPhantomBlow>("PhantomBlow1", this, &CPhantomBlow::AnimationFinish);

	m_Sprite2->CreateAnimationInstance<CAnimationSequence2DInstance>();
	m_Anim2 = m_Sprite2->GetAnimationInstance();
	m_Anim2->AddAnimation(TEXT("Skill/PhantomBlow/PhantomBlow0.sqc"), ANIMATION_PATH, "PhantomBlow2", false);

	//m_Anim2->AddAnimation("PhantomBlow2", "PhantomBlow2", false);

	m_Muzzle->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->AddCollisionCallback<CPhantomBlow>(Collision_State::Begin, this, &CPhantomBlow::OnCollisionBegin);
	m_Body->SetCollisionProfile("PlayerAttack");

	m_Damage = 0;

	return true;
}

void CPhantomBlow::Update(float DeltaTime)
{
	CSkillManager::Update(DeltaTime);

	int Frame = m_Anim1->GetFrame();
}

void CPhantomBlow::PostUpdate(float DeltaTime)
{
	CSkillManager::PostUpdate(DeltaTime);
}

CPhantomBlow* CPhantomBlow::Clone()
{
	return new CPhantomBlow(*this);
}

void CPhantomBlow::SetEnable()
{
	CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

	if (!Player)
	{
		m_Body->Enable(false);
		Enable(false);

		return;
	}

	if (Player->GetFlip())
	{
		m_Anim1->SetAnimFlip(Player->GetFlip());
		m_Anim2->SetAnimFlip(Player->GetFlip());

		m_Sprite1->SetRelativeScale(616.f, 300.f, 2.f);
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
		m_Anim1->SetAnimFlip(Player->GetFlip());
		m_Anim2->SetAnimFlip(Player->GetFlip());

		m_Sprite1->SetRelativeScale(616.f, 300.f, 2.f);
		m_Sprite1->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite1->SetRelativePos(-161.f, 35.5f, 11.f);

		m_Sprite2->SetRelativeScale(230.f, 110.f, 2.f);
		m_Sprite2->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite2->SetRelativePos(80.f, 5.f, 11.f);

		m_Body->SetRelativePos(m_Sprite1->GetRelativePos());
		m_Body->SetExtent(154.f, 77.5f);
		m_Body->SetOffset(154.f, -77.5f, 0.f);
	}

	m_Body->Enable(true);
	Enable(true);

	m_Anim1->AnimationReStart();
	m_Anim2->AnimationReStart();
}

void CPhantomBlow::OnCollisionBegin(const CollisionResult& result)
{
	m_obj = dynamic_cast<CMonsterManager*>(result.Dest->GetGameObject());

	if (!m_obj)
	{
		return;
	}

	if (!m_Anim1->GetCurrentAnimation())
	{
		return;
	}

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

	m_Body->Enable(false);
}

void CPhantomBlow::AnimationFinish()
{
	if (m_obj)
	{
		if (m_obj->GetCharacterInfo().HP <= 0)
		{
			m_obj->SetDie(true);
		}

		else
		{
			m_obj = nullptr;
		}
	}

	m_Body->Enable(false);

	//Destroy();

	Enable(false);
}

void CPhantomBlow::OnCollision()
{
	m_Body->Enable(true);
}

void CPhantomBlow::OffCollision()
{
	m_Body->Enable(false);
}

void CPhantomBlow::Attack()
{
	if (!m_Anim1->GetCurrentAnimation())
	{
		return;
	}

	if (m_obj)
	{
		int Frame = m_Anim1->GetFrame();

		CDamageFont* DamageFont = m_Scene->CreateGameObject<CDamageFont>("DamagrFont");

		if (!DamageFont)
		{
			return;
		}

		DamageFont->SetWorldPos(m_TargetPos.x - 31.f, m_TargetPos.y + (m_TargetSize.y) + (Frame * 30), 1);

		m_Damage = 10;

		DamageFont->SetDamageNumber(m_Damage);

		m_obj->SetDamage((float)m_Damage);
	}
}
