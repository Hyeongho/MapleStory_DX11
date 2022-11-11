#include "LeftAttack1AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"

CLeftAttack1AreaWarning::CLeftAttack1AreaWarning()
{
	SetTypeID<CLeftAttack1AreaWarning>();
}

CLeftAttack1AreaWarning::CLeftAttack1AreaWarning(const CLeftAttack1AreaWarning& obj) : CGameObject(obj)
{
}

CLeftAttack1AreaWarning::~CLeftAttack1AreaWarning()
{
}

void CLeftAttack1AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

void CLeftAttack1AreaWarning::Start()
{
	CGameObject::Start();
}

bool CLeftAttack1AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("LeftAttack1AreaWarning");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	//m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Left/LeftAttack1AreaWarning.sqc"), ANIMATION_PATH, "LeftAttack1AreaWarning", false, 1.68f);
	Anim->SetEndFunction("LeftAttack1AreaWarning", this, &CLeftAttack1AreaWarning::AnimationFinish);

	m_Sprite->SetRelativeScale(547.f, 647.f, 1.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CLeftAttack1AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CLeftAttack1AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CLeftAttack1AreaWarning* CLeftAttack1AreaWarning::Clone()
{
	return  new CLeftAttack1AreaWarning(*this);
}

void CLeftAttack1AreaWarning::OnCollisionBegin(const CollisionResult& result)
{
}

void CLeftAttack1AreaWarning::AnimationFinish()
{
	Destroy();
}
