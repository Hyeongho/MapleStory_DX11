#include "BodyAttack2Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CBodyAttack2Hit::CBodyAttack2Hit()
{
}

CBodyAttack2Hit::CBodyAttack2Hit(const CBodyAttack2Hit& obj) : CGameObject(obj)
{
}

CBodyAttack2Hit::~CBodyAttack2Hit()
{
}

void CBodyAttack2Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogBodyAttack2Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Body/BalrogBodyAttack2Hit.sqc"), ANIMATION_PATH, "BalrogBodyAttack2Hit", false, 0.5f);

	Anim->SetEndFunction<CBodyAttack2Hit>("BalrogBodyAttack2Hit", this, &CBodyAttack2Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(100.f, 126.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CBodyAttack2Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CBodyAttack2Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack2Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack2Hit* CBodyAttack2Hit::Clone()
{
	return new CBodyAttack2Hit(*this);
}

void CBodyAttack2Hit::SetFlip(bool Flip)
{
}

void CBodyAttack2Hit::AnimationFinish()
{
	Destroy();
}
