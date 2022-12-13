#include "BodyAttack3Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CBodyAttack3Hit::CBodyAttack3Hit()
{
}

CBodyAttack3Hit::CBodyAttack3Hit(const CBodyAttack3Hit& obj) : CGameObject(obj)
{
}

CBodyAttack3Hit::~CBodyAttack3Hit()
{
}

void CBodyAttack3Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogBodyAttack3Hit");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Body/BalrogBodyAttack3Hit.sqc"), ANIMATION_PATH, "BalrogBodyAttack3Hit", false, 0.5f);

	Anim->SetEndFunction<CBodyAttack3Hit>("BalrogBodyAttack3Hit", this, &CBodyAttack3Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(128.f, 116.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CBodyAttack3Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CBodyAttack3Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack3Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack3Hit* CBodyAttack3Hit::Clone()
{
	return new CBodyAttack3Hit(*this);
}

void CBodyAttack3Hit::SetFlip(bool Flip)
{
}

void CBodyAttack3Hit::AnimationFinish()
{
	Destroy();
}
