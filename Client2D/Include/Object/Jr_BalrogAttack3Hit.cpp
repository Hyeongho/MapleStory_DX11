#include "Jr_BalrogAttack3Hit.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CJr_BalrogAttack3Hit::CJr_BalrogAttack3Hit()
{
}

CJr_BalrogAttack3Hit::CJr_BalrogAttack3Hit(const CJr_BalrogAttack3Hit& obj) : CGameObject(obj)
{
}

CJr_BalrogAttack3Hit::~CJr_BalrogAttack3Hit()
{
}

void CJr_BalrogAttack3Hit::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("Jr_BalrogAttack2Ball");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack3Hit.sqc"), ANIMATION_PATH, "Jr_BalrogAttack3Hit", false, 0.57f);

	Anim->SetEndFunction<CJr_BalrogAttack3Hit>("Jr_BalrogAttack3Hit", this, &CJr_BalrogAttack3Hit::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(101.f, 95.f, 1.f);

	m_Sprite->SetLayerName("Effect");
}

bool CJr_BalrogAttack3Hit::Init()
{
	CGameObject::Init();

	return true;
}

void CJr_BalrogAttack3Hit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJr_BalrogAttack3Hit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack3Hit* CJr_BalrogAttack3Hit::Clone()
{
	return new CJr_BalrogAttack3Hit(*this);
}

void CJr_BalrogAttack3Hit::AnimationFinish()
{
	Destroy();
}
