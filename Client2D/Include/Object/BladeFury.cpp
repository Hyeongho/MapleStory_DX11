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

CBladeFury::CBladeFury(const CBladeFury& obj) : CGameObject(obj)
{
}

CBladeFury::~CBladeFury()
{
}

void CBladeFury::SetCollisionProfile(const std::string& Name)
{
}

bool CBladeFury::Init()
{
	CGameObject::Init();

	CPlayer2D* Player = (CPlayer2D*)m_Scene->GetPlayerObject();

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
	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();
	Anim->AddAnimation(TEXT("Skill/BladeFury.sqc"), ANIMATION_PATH, "BladeFuryEffect", false, 1.0f);

	Anim->AddNotify<CBladeFury>("BladeFuryEffect", "Destroy", 14, this, &CBladeFury::AnimationFinish);

	m_Muzzle->SetPivot(0.5f, 0.5f, 0.f);

	if (!Player->GetFlip())
	{
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
	}

	return true;
}

void CBladeFury::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBladeFury::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBladeFury* CBladeFury::Clone()
{
	return new CBladeFury(*this);
}

void CBladeFury::OnCollisionBegin(const CollisionResult& result)
{
}

void CBladeFury::AnimationFinish()
{
	CPlayerManager::GetInst()->SetPlayerAttack(Player_Attack::Attack_End);

	Destroy();
}
