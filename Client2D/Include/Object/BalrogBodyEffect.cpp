#include "BalrogBodyEffect.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"

CBalrogBodyEffect::CBalrogBodyEffect()
{
}

CBalrogBodyEffect::CBalrogBodyEffect(const CBalrogBodyEffect& obj)
{
}

CBalrogBodyEffect::~CBalrogBodyEffect()
{
}

void CBalrogBodyEffect::SetCollisionProfile(const std::string& Name)
{
}

bool CBalrogBodyEffect::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogBodyEffect");

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	return true;
}

void CBalrogBodyEffect::Update(float DeltaTime)
{
}

void CBalrogBodyEffect::PostUpdate(float DeltaTime)
{
}

CBalrogBodyEffect* CBalrogBodyEffect::Clone()
{
	return nullptr;
}

void CBalrogBodyEffect::OnCollisionBegin(const CollisionResult& result)
{
}

void CBalrogBodyEffect::AnimationFinish()
{
}
