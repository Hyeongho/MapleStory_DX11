#include "BodyAttack1AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"

CBodyAttack1AreaWarning::CBodyAttack1AreaWarning()
{
	SetTypeID<CBodyAttack1AreaWarning>();
}

CBodyAttack1AreaWarning::CBodyAttack1AreaWarning(const CBodyAttack1AreaWarning& obj) : CGameObject(obj)
{
}

CBodyAttack1AreaWarning::~CBodyAttack1AreaWarning()
{
}

void CBodyAttack1AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

bool CBodyAttack1AreaWarning::Init()
{
	CGameObject::Init();

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Sprite = CreateComponent<CSpriteComponent>("BladeFury");

	m_Sprite->SetLayerName("Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Muzzle);

	m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();
	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();
	Anim->AddAnimation(TEXT("Monster/Balrog/Body/Attack1AreaWarning.sqc"), ANIMATION_PATH, "Attack1AreaWarning", false, 1.0f);

	return true;
}

void CBodyAttack1AreaWarning::Update(float DeltaTime)
{
}

void CBodyAttack1AreaWarning::PostUpdate(float DeltaTime)
{
}

CBodyAttack1AreaWarning* CBodyAttack1AreaWarning::Clone()
{
	return  new CBodyAttack1AreaWarning(*this);;
}

void CBodyAttack1AreaWarning::OnCollisionBegin(const CollisionResult& result)
{
}

void CBodyAttack1AreaWarning::AnimationFinish()
{
}
