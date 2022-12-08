#include "Jr_BalrogAttack1Effect.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Jr_Balrog.h"
#include "Jr_BalrogAttack1Hit.h"
#include "Player2D.h"

CJr_BalrogAttack1Effect::CJr_BalrogAttack1Effect() : m_Target(false)
{
}

CJr_BalrogAttack1Effect::CJr_BalrogAttack1Effect(const CJr_BalrogAttack1Effect& obj) : CGameObject(obj)
{
}

CJr_BalrogAttack1Effect::~CJr_BalrogAttack1Effect()
{
}

void CJr_BalrogAttack1Effect::SetCollisionProfile(const std::string& Name)
{
}

void CJr_BalrogAttack1Effect::Start()
{
	CGameObject::Start();

	m_Body->Enable(false);
	Enable(false);
}

bool CJr_BalrogAttack1Effect::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Jr_BalrogAttack1Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Body->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/jr_Balrog/Jr_BalrogAttack1Effect.sqc"), ANIMATION_PATH, "Jr_BalrogAttack1Effect", false, 0.635f);
	m_Anim->SetEndFunction("Jr_BalrogAttack1Effect", this, &CJr_BalrogAttack1Effect::AnimationFinish);

	m_Body->AddCollisionCallback<CJr_BalrogAttack1Effect>(Collision_State::Begin, this, &CJr_BalrogAttack1Effect::OnCollisionBegin);
	m_Body->AddCollisionCallback<CJr_BalrogAttack1Effect>(Collision_State::End, this, &CJr_BalrogAttack1Effect::OnCollisionEnd);

	m_Sprite->SetRelativeScale(114.f, 111.f, 1.f);

	m_Body->SetExtent(250.f, 250.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CJr_BalrogAttack1Effect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJr_BalrogAttack1Effect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack1Effect* CJr_BalrogAttack1Effect::Clone()
{
	return  new CJr_BalrogAttack1Effect(*this);
}

void CJr_BalrogAttack1Effect::SetEnable(CJr_Balrog* Balrog)
{
	if (!Balrog->GetFlip())
	{
		m_Anim->SetAnimFlip(false);

		m_Sprite->SetRelativeScale(114.f, 111.f, 1.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(359.f, 372.5f, 1.f);
	}

	else
	{
		m_Anim->SetAnimFlip(true);

		m_Sprite->SetRelativeScale(114.f, 111.f, 1.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(305.f, 325.f, 1.f);
	}

	m_Body->Enable(true);
	Enable(true);

	m_Anim->AnimationReStart();
}

void CJr_BalrogAttack1Effect::OnCollisionBegin(const CollisionResult& result)
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

void CJr_BalrogAttack1Effect::OnCollisionEnd(const CollisionResult& result)
{
	m_Target = false;
}

void CJr_BalrogAttack1Effect::AnimationFinish()
{
	if (m_Target)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (Player)
		{
			CJr_BalrogAttack1Hit* Jr_BalrogAttack1Hit = m_Scene->CreateGameObject<CJr_BalrogAttack1Hit>("Jr_BalrogAttack1Hit", "Jr_BalrogAttack1Hit", Player->GetWorldPos());

			float Dis = Player->GetWorldPos().x - GetWorldPos().x;

			if (Dis >= 0)
			{
				Jr_BalrogAttack1Hit->SetFlip(true);
			}

			else
			{
				Jr_BalrogAttack1Hit->SetFlip(false);
			}

			CResourceManager::GetInst()->SoundPlay("Jr_BalrogCharDam1");

			Player->SetDamage(10.f);

			Player->SetHurt(true);
		}
	}

	m_Body->Enable(false);
	Enable(false);
}
