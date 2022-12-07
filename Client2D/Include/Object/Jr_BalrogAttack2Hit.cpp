#include "Jr_BalrogAttack2Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CJr_BalrogAttack2Hit::CJr_BalrogAttack2Hit()
{
}

CJr_BalrogAttack2Hit::CJr_BalrogAttack2Hit(const CJr_BalrogAttack2Hit& obj) : CGameObject(obj)
{
}

CJr_BalrogAttack2Hit::~CJr_BalrogAttack2Hit()
{
}

void CJr_BalrogAttack2Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("Jr_BalrogAttack2Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack2Hit.sqc"), ANIMATION_PATH, "Jr_BalrogAttack2Hit", false, 0.4f);

	Anim->SetEndFunction<CJr_BalrogAttack2Hit>("Jr_BalrogAttack2Hit", this, &CJr_BalrogAttack2Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(106.f, 120.f, 1.f);
}

bool CJr_BalrogAttack2Hit::Init()
{
	return true;
}

void CJr_BalrogAttack2Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJr_BalrogAttack2Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack2Hit* CJr_BalrogAttack2Hit::Clone()
{
	return new CJr_BalrogAttack2Hit(*this);
}

void CJr_BalrogAttack2Hit::SetFlip(bool Flip)
{
}

void CJr_BalrogAttack2Hit::AnimationFinish()
{
	Destroy();
}
