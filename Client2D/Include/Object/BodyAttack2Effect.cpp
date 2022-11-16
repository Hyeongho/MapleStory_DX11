#include "BodyAttack2Effect.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"

CBodyAttack2Effect::CBodyAttack2Effect()
{
	SetTypeID<CBodyAttack2Effect>();
}

CBodyAttack2Effect::CBodyAttack2Effect(const CBodyAttack2Effect& obj) : CGameObject(obj)
{
}

CBodyAttack2Effect::~CBodyAttack2Effect()
{
}

void CBodyAttack2Effect::SetCollisionProfile(const std::string& Name)
{
}

void CBodyAttack2Effect::Start()
{
	CGameObject::Start();
}

bool CBodyAttack2Effect::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("BodyAttack2Effect");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	//m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Body/BodyAttack2Effect.sqc"), ANIMATION_PATH, "BodyAttack2Effect", false, 1.68f);
	Anim->SetEndFunction("BodyAttack2Effect", this, &CBodyAttack2Effect::AnimationFinish);

	m_Sprite->SetRelativeScale(547.f, 647.f, 1.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CBodyAttack2Effect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack2Effect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack2Effect* CBodyAttack2Effect::Clone()
{
	return new CBodyAttack2Effect(*this);
}

void CBodyAttack2Effect::OnCollisionBegin(const CollisionResult& result)
{
}

void CBodyAttack2Effect::AnimationFinish()
{
	Destroy();
}
