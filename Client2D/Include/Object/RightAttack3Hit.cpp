#include "RightAttack3Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CRightAttack3Hit::CRightAttack3Hit()
{
}

CRightAttack3Hit::CRightAttack3Hit(const CRightAttack3Hit& obj) : CGameObject(obj)
{
}

CRightAttack3Hit::~CRightAttack3Hit()
{
}

void CRightAttack3Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogRightAttack3Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Right/BalrogRightAttack3Hit.sqc"), ANIMATION_PATH, "BalrogRightAttack3Hit", false, 0.5f);

	Anim->SetEndFunction<CRightAttack3Hit>("BalrogRightAttack3Hit", this, &CRightAttack3Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(162.f, 135.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CRightAttack3Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CRightAttack3Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRightAttack3Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRightAttack3Hit* CRightAttack3Hit::Clone()
{
	return new CRightAttack3Hit(*this);
}

void CRightAttack3Hit::SetFlip(bool Flip)
{
}

void CRightAttack3Hit::AnimationFinish()
{
	Destroy();
}
