#include "LeftAttack1Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CLeftAttack1Hit::CLeftAttack1Hit()
{
}

CLeftAttack1Hit::CLeftAttack1Hit(const CLeftAttack1Hit& obj) : CGameObject(obj)
{
}

CLeftAttack1Hit::~CLeftAttack1Hit()
{
}

void CLeftAttack1Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogLeftAttack1Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Left/BalrogLeftAttack1Hit.sqc"), ANIMATION_PATH, "BalrogLeftAttack1Hit", false, 0.6f);

	Anim->SetEndFunction<CLeftAttack1Hit>("BalrogLeftAttack1Hit", this, &CLeftAttack1Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(128.f, 116.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CLeftAttack1Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CLeftAttack1Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CLeftAttack1Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CLeftAttack1Hit* CLeftAttack1Hit::Clone()
{
	return new CLeftAttack1Hit(*this);
}

void CLeftAttack1Hit::SetFlip(bool Flip)
{
}

void CLeftAttack1Hit::AnimationFinish()
{
	Destroy();
}
