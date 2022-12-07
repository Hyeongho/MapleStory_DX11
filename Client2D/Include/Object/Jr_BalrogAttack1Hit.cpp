#include "Jr_BalrogAttack1Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CJr_BalrogAttack1Hit::CJr_BalrogAttack1Hit()
{
}

CJr_BalrogAttack1Hit::CJr_BalrogAttack1Hit(const CJr_BalrogAttack1Hit& obj) : CGameObject(obj)
{
}

CJr_BalrogAttack1Hit::~CJr_BalrogAttack1Hit()
{
}

void CJr_BalrogAttack1Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("Jr_BalrogAttack1Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack1Hit.sqc"), ANIMATION_PATH, "Jr_BalrogAttack1Hit", false, 0.78f);

	Anim->SetEndFunction<CJr_BalrogAttack1Hit>("Jr_BalrogAttack1Hit", this, &CJr_BalrogAttack1Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(224.f, 215.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CJr_BalrogAttack1Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CJr_BalrogAttack1Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJr_BalrogAttack1Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack1Hit* CJr_BalrogAttack1Hit::Clone()
{
	return new CJr_BalrogAttack1Hit(*this);
}

void CJr_BalrogAttack1Hit::SetFlip(bool Flip)
{
	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	if (!Anim)
	{
		return;
	}

	Anim->SetAnimFlip(Flip);

	//m_Sprite->SetFlip(Flip);
}

void CJr_BalrogAttack1Hit::AnimationFinish()
{
	Destroy();
}