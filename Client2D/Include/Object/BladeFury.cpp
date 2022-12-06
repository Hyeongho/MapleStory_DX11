#include "BladeFury.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Player2D.h"
#include "PlayerManager.h"

CBladeFury::CBladeFury()
{
	SetTypeID<CBladeFury>();
}

CBladeFury::CBladeFury(const CBladeFury& obj) : CSkillManager(obj)
{
}

CBladeFury::~CBladeFury()
{
}

void CBladeFury::SetCollisionProfile(const std::string& Name)
{
}

void CBladeFury::Start()
{
	CSkillManager::Start();

	m_Body->Enable(false);

	Enable(false);
}

bool CBladeFury::Init()
{
	CSkillManager::Init();

	CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

	if (!Player)
	{
		return false;
	}

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Sprite = CreateComponent<CSpriteComponent>("BladeFury");

	m_Sprite->SetLayerName("Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Muzzle);

	m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();
	m_Anim = m_Sprite->GetAnimationInstance();
	m_Anim->AddAnimation(TEXT("Skill/BladeFury.sqc"), ANIMATION_PATH, "BladeFuryEffect", false, 1.0f);

	m_Anim->SetEndFunction<CBladeFury>("BladeFuryEffect", this, &CBladeFury::AnimationFinish);

	m_Muzzle->SetPivot(0.5f, 0.5f, 0.f);

	/*if (!Player->GetFlip())
	{
		Anim->SetAnimFlip(false);

		m_Sprite->SetRelativeScale(712.f, 586.f, 2.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(-23.5f, 112.f, 11.f);
	}

	else
	{
		Anim->SetAnimFlip(false);

		m_Sprite->SetRelativeScale(712.f, 586.f, 2.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(23.5f, 112.f, 11.f);
	}*/

	return true;
}

void CBladeFury::Update(float DeltaTime)
{
	CSkillManager::Update(DeltaTime);
}

void CBladeFury::PostUpdate(float DeltaTime)
{
	CSkillManager::PostUpdate(DeltaTime);
}

CBladeFury* CBladeFury::Clone()
{
	return new CBladeFury(*this);
}

void CBladeFury::SetEnable()
{
	CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

	if (!Player)
	{
		m_Body->Enable(false);
		Enable(false);

		return;
	}

	if (!Player->GetFlip())
	{
		m_Anim->SetAnimFlip(false);

		m_Sprite->SetRelativeScale(712.f, 586.f, 2.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(23.5f, 112.f, 11.f);
	}

	else
	{
		m_Anim->SetAnimFlip(true);

		m_Sprite->SetRelativeScale(712.f, 586.f, 2.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(-23.5f, 112.f, 11.f);
	}

	m_Body->Enable(true);
	Enable(true);

	m_Anim->AnimationReStart();
}

void CBladeFury::OnCollisionBegin(const CollisionResult& result)
{
	for (int i = 0; i < 6; i++)
	{
		m_obj = dynamic_cast<CMonsterManager*>(result.Dest->GetGameObject());

		if (!m_obj)
		{
			return;
		}

		if (!m_Anim->GetCurrentAnimation())
		{
			return;
		}

		int Frame = m_Anim->GetFrame();

		if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Monster)
		{
			for (int i = 1; i <= 9; i++)
			{
				//result.Dest->GetGameObject()->SetDamage(10);

				m_TargetPos = m_obj->GetWorldPos();
				m_TargetSize = m_obj->GetSize();

				//m_obj->SetDamage(10);

				m_Anim->AddNotify<CBladeFury>("BladeFuryEffect", "BladeFuryEffect", i, this, &CBladeFury::Attack);
			}
		}
	}

	m_Body->Enable(false);
}

void CBladeFury::AnimationFinish()
{
	CPlayerManager::GetInst()->SetPlayerAttack(Player_Attack::Attack_End);

	m_Body->Enable(false);

	//Destroy();

	Enable(false);
}

void CBladeFury::Attack()
{
}
