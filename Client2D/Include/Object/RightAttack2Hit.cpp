#include "RightAttack2Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CRightAttack2Hit::CRightAttack2Hit()
{
}

CRightAttack2Hit::CRightAttack2Hit(const CRightAttack2Hit& obj) : CGameObject(obj)
{
}

CRightAttack2Hit::~CRightAttack2Hit()
{
}

void CRightAttack2Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogRightAttack2Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Right/BalrogRightAttack2Hit.sqc"), ANIMATION_PATH, "BalrogRightAttack2Hit", false, 0.5f);

	Anim->SetEndFunction<CRightAttack2Hit>("BalrogRightAttack2Hit", this, &CRightAttack2Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(123.f, 94.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CRightAttack2Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CRightAttack2Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRightAttack2Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRightAttack2Hit* CRightAttack2Hit::Clone()
{
	return new CRightAttack2Hit(*this);
}

void CRightAttack2Hit::SetFlip(bool Flip)
{
}

void CRightAttack2Hit::AnimationFinish()
{
	Destroy();
}
