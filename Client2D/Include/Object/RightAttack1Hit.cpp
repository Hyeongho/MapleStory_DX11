#include "RightAttack1Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CRightAttack1Hit::CRightAttack1Hit()
{
}

CRightAttack1Hit::CRightAttack1Hit(const CRightAttack1Hit& obj) : CGameObject(obj)
{
}

CRightAttack1Hit::~CRightAttack1Hit()
{
}

void CRightAttack1Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogRightAttack1Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Right/BalrogRightAttack1Hit.sqc"), ANIMATION_PATH, "BalrogRightAttack1Hit", false, 0.5f);

	Anim->SetEndFunction<CRightAttack1Hit>("BalrogRightAttack1Hit", this, &CRightAttack1Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(128.f, 116.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CRightAttack1Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CRightAttack1Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRightAttack1Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRightAttack1Hit* CRightAttack1Hit::Clone()
{
	return new CRightAttack1Hit(*this);
}

void CRightAttack1Hit::SetFlip(bool Flip)
{
}

void CRightAttack1Hit::AnimationFinish()
{
	Destroy();
}
