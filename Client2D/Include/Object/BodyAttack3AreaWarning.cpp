#include "BodyAttack3AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"

CBodyAttack3AreaWarning::CBodyAttack3AreaWarning()
{
	SetTypeID<CBodyAttack3AreaWarning>();
}

CBodyAttack3AreaWarning::CBodyAttack3AreaWarning(const CBodyAttack3AreaWarning& obj) : CGameObject(obj)
{
}

CBodyAttack3AreaWarning::~CBodyAttack3AreaWarning()
{
}

void CBodyAttack3AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

void CBodyAttack3AreaWarning::Start()
{
	CGameObject::Start();
}

bool CBodyAttack3AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("CBodyAttack3AreaWarning");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Sprite->SetLayerName("Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();
	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();
	Anim->AddAnimation(TEXT("Monster/Balrog/Body/Attack3AreaWarning.sqc"), ANIMATION_PATH, "Attack3AreaWarning", false, 2.52f);
	//Anim->AddAnimation("Attack3AreaWarning", "Attack3AreaWarning", false, 2.52f);

	Anim->SetEndFunction("Attack3AreaWarning", this, &CBodyAttack3AreaWarning::AnimationFinish);

	m_Sprite->SetRelativeScale(160.f, 499.f, 1.f);

	return true;
}

void CBodyAttack3AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBodyAttack3AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBodyAttack3AreaWarning* CBodyAttack3AreaWarning::Clone()
{
	return  new CBodyAttack3AreaWarning(*this);
}

void CBodyAttack3AreaWarning::OnCollisionBegin(const CollisionResult& result)
{
}

void CBodyAttack3AreaWarning::AnimationFinish()
{
	Destroy();
}
