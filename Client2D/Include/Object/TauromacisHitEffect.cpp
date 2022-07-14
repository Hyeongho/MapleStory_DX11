#include "TauromacisHitEffect.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CTauromacisHitEffect::CTauromacisHitEffect()
{
}

CTauromacisHitEffect::CTauromacisHitEffect(const CTauromacisHitEffect& obj)
{
}

CTauromacisHitEffect::~CTauromacisHitEffect()
{
}

void CTauromacisHitEffect::Start()
{
	CGameObject::Start();
}

bool CTauromacisHitEffect::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("TauromacisHitEffect");

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Tauromacis/TauromacisHitEffect.sqc"), ANIMATION_PATH, "TauromacisHitEffect", true, 0.3f);
	Anim->AddNotify<CTauromacisHitEffect>("TauromacisHitEffect", "TauromacisHitEffect", 3, this, &CTauromacisHitEffect::AnimationFinish);

	m_Sprite->SetRelativeScale(250.f, 250.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.f, 0.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CTauromacisHitEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTauromacisHitEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTauromacisHitEffect* CTauromacisHitEffect::Clone()
{
	return new CTauromacisHitEffect(*this);
}

void CTauromacisHitEffect::AnimationFinish()
{
	Destroy();
}
