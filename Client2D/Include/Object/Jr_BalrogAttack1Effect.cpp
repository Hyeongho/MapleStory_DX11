#include "Jr_BalrogAttack1Effect.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Jr_Balrog.h"

CJr_BalrogAttack1Effect::CJr_BalrogAttack1Effect()
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

	m_Sprite = CreateComponent<CSpriteComponent>("CJr_BalrogAttack1Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/jr_Balrog/Jr_BalrogAttack1Effect.sqc"), ANIMATION_PATH, "Jr_BalrogAttack1Effect", false, 0.635f);
	m_Anim->SetEndFunction("Jr_BalrogAttack1Effect", this, &CJr_BalrogAttack1Effect::AnimationFinish);

	m_Sprite->SetRelativeScale(114.f, 111.f, 1.f);

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
}

void CJr_BalrogAttack1Effect::AnimationFinish()
{
	m_Body->Enable(false);
	Enable(false);
}
