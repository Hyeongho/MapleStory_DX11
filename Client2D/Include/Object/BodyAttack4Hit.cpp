#include "BodyAttack4Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CBodyAttack4Hit::CBodyAttack4Hit()
{
}

CBodyAttack4Hit::CBodyAttack4Hit(const CBodyAttack4Hit& obj) : CGameObject(obj)
{
}

CBodyAttack4Hit::~CBodyAttack4Hit()
{
}

void CBodyAttack4Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogBodyAttack4Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Body/BalrogBodyAttack4Hit.sqc"), ANIMATION_PATH, "BalrogBodyAttack4Hit", false, 0.99f);

	Anim->SetEndFunction<CBodyAttack4Hit>("BalrogBodyAttack4Hit", this, &CBodyAttack4Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(157.f, 153.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CBodyAttack4Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CBodyAttack4Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack4Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack4Hit* CBodyAttack4Hit::Clone()
{
	return new CBodyAttack4Hit(*this);
}

void CBodyAttack4Hit::SetFlip(bool Flip)
{
}

void CBodyAttack4Hit::AnimationFinish()
{
}
