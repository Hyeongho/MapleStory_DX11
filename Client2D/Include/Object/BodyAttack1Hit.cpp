#include "BodyAttack1Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CBodyAttack1Hit::CBodyAttack1Hit()
{
}

CBodyAttack1Hit::CBodyAttack1Hit(const CBodyAttack1Hit& obj) : CGameObject(obj)
{
}

CBodyAttack1Hit::~CBodyAttack1Hit()
{
}

void CBodyAttack1Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogBodyAttack1Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Body/BalrogBodyAttack1Hit.sqc"), ANIMATION_PATH, "BalrogBodyAttack1Hit", false, 0.6f);

	Anim->SetEndFunction<CBodyAttack1Hit>("BalrogBodyAttack1Hit", this, &CBodyAttack1Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(126.f, 111.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CBodyAttack1Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CBodyAttack1Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack1Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack1Hit* CBodyAttack1Hit::Clone()
{
	return new CBodyAttack1Hit(*this);
}

void CBodyAttack1Hit::SetFlip(bool Flip)
{
}

void CBodyAttack1Hit::AnimationFinish()
{
	Destroy();
}
