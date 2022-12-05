#include "Jr_BalrogAttack3Effect.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Jr_Balrog.h"

CJr_BalrogAttack3Effect::CJr_BalrogAttack3Effect()
{
}

CJr_BalrogAttack3Effect::CJr_BalrogAttack3Effect(const CJr_BalrogAttack3Effect& obj) : CGameObject(obj)
{
}

CJr_BalrogAttack3Effect::~CJr_BalrogAttack3Effect()
{
}

void CJr_BalrogAttack3Effect::SetCollisionProfile(const std::string& Name)
{
}

void CJr_BalrogAttack3Effect::Start()
{
	CGameObject::Start();

	m_Body->Enable(false);
	Enable(false);
}

bool CJr_BalrogAttack3Effect::Init()
{
	CGameObject::Init();

	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Sprite = CreateComponent<CSpriteComponent>("CJr_BalrogAttack3Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Muzzle);

	m_Muzzle->AddChild(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/jr_Balrog/Jr_BalrogAttack3Effect.sqc"), ANIMATION_PATH, "Jr_BalrogAttack3Effect", false, 0.4f);
	m_Anim->SetEndFunction("Jr_BalrogAttack3Effect", this, &CJr_BalrogAttack3Effect::AnimationFinish);

	m_Sprite->SetRelativeScale(243.f, 112.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.5);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CJr_BalrogAttack3Effect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJr_BalrogAttack3Effect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack3Effect* CJr_BalrogAttack3Effect::Clone()
{
	return new CJr_BalrogAttack3Effect(*this);
}

void CJr_BalrogAttack3Effect::SetEnable(CJr_Balrog* Balrog)
{
	if (!Balrog)
	{
		m_Body->Enable(false);
		Enable(false);

		return;
	}

	if (!Balrog->GetFlip())
	{
		m_Anim->SetAnimFlip(false);
	}

	else
	{
		m_Anim->SetAnimFlip(true);
	}

	m_Body->Enable(true);
	Enable(true);

	m_Anim->AnimationReStart();
}

void CJr_BalrogAttack3Effect::OnCollisionBegin(const CollisionResult& result)
{
}

void CJr_BalrogAttack3Effect::AnimationFinish()
{
	m_Body->Enable(false);
	Enable(false);
}