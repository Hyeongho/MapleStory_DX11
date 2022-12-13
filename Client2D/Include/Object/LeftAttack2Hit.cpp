#include "LeftAttack2Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CLeftAttack2Hit::CLeftAttack2Hit()
{
}

CLeftAttack2Hit::CLeftAttack2Hit(const CLeftAttack2Hit& obj) : CGameObject(obj)
{
}

CLeftAttack2Hit::~CLeftAttack2Hit()
{
}

void CLeftAttack2Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogLeftAttack2Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Left/BalrogLeftAttack2Hit.sqc"), ANIMATION_PATH, "BalrogLeftAttack2Hit", false, 0.72f);

	Anim->SetEndFunction<CLeftAttack2Hit>("BalrogLeftAttack2Hit", this, &CLeftAttack2Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(112.f, 111.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CLeftAttack2Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CLeftAttack2Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CLeftAttack2Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CLeftAttack2Hit* CLeftAttack2Hit::Clone()
{
	return new CLeftAttack2Hit(*this);
}

void CLeftAttack2Hit::SetFlip(bool Flip)
{
}

void CLeftAttack2Hit::AnimationFinish()
{
	Destroy();
}
