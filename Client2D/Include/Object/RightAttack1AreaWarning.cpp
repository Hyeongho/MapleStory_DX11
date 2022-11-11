#include "RightAttack1AreaWarning.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Balrog.h"

CRightAttack1AreaWarning::CRightAttack1AreaWarning()
{
	SetTypeID<CRightAttack1AreaWarning>();
}

CRightAttack1AreaWarning::CRightAttack1AreaWarning(const CRightAttack1AreaWarning& obj) : CGameObject(obj)
{
}

CRightAttack1AreaWarning::~CRightAttack1AreaWarning()
{
}

void CRightAttack1AreaWarning::SetCollisionProfile(const std::string& Name)
{
}

void CRightAttack1AreaWarning::Start()
{
	CGameObject::Start();
}

bool CRightAttack1AreaWarning::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("RightAttack1AreaWarning");

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	//m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Balrog/Right/RightAttack1AreaWarning.sqc"), ANIMATION_PATH, "RightAttack1AreaWarning", false, 1.68f);
	Anim->SetEndFunction("RightAttack1AreaWarning", this, &CRightAttack1AreaWarning::AnimationFinish);

	m_Sprite->SetRelativeScale(139.f, 192.f, 1.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CRightAttack1AreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRightAttack1AreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRightAttack1AreaWarning* CRightAttack1AreaWarning::Clone()
{
	return  new CRightAttack1AreaWarning(*this);
}

void CRightAttack1AreaWarning::OnCollisionBegin(const CollisionResult& result)
{
}

void CRightAttack1AreaWarning::AnimationFinish()
{
	Destroy();
}
