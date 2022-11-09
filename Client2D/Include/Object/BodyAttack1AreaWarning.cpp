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

void CBodyAttack1AreaWarning::Start()
{
	CGameObject::Start();
}

bool CBodyAttack1AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Attack1AreaWarning");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	//m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Body/Attack1AreaWarning.sqc"), ANIMATION_PATH, "Attack1AreaWarning", false, 1.68f);
	Anim->SetEndFunction("Attack1AreaWarning", this, &CBodyAttack1AreaWarning::AnimationFinish);

	m_Sprite->SetRelativeScale(547.f, 647.f, 1.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CBodyAttack1AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack1AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack1AreaWarning* CBodyAttack1AreaWarning::Clone()
{
	return  new CBodyAttack1AreaWarning(*this);
}

void CBodyAttack1AreaWarning::OnCollisionBegin(const CollisionResult& result)
{
}

void CBodyAttack1AreaWarning::AnimationFinish()
{
	Destroy();
}
