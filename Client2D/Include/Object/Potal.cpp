#include "Potal.h"
#include "Resource/Material/Material.h"
#include "PlayerManager.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "../Scene/LoadingSeolhuiui.h"
#include "../Scene/LoadingEToTemple.h"
#include "../Scene/LoadingAnotherDoor.h"
#include "../Scene/MainScene.h"
#include "Scene/SceneManager.h"
#include "../Widget/Fade.h"
#include "../ClientManager.h"

CPotal::CPotal()
{
}

CPotal::CPotal(const CPotal& obj) : CGameObject(obj)
{
}

CPotal::~CPotal()
{
	
}

void CPotal::Start()
{
	CGameObject::Start();
}

bool CPotal::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Sprite = CreateComponent<CSpriteComponent>("Potal");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Sprite->SetTransparency(true);

	m_Sprite->SetLayerName("Potal");

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Object/Potal1.sqc"), ANIMATION_PATH, "Idle", true);

	m_Body->AddCollisionCallback<CPotal>(Collision_State::Begin, this, &CPotal::CollisionCallbackBegin);
	m_Body->AddCollisionCallback<CPotal>(Collision_State::End, this, &CPotal::CollisionCallbackEnd);

	m_Body->SetCollisionProfile("Potal");

	m_Sprite->SetRelativeScale(104.f, 142.f, 1.f);

	m_Body->SetOffset(52.f, 71.f, 1.f);
	m_Body->SetExtent(52.f, 71.f);

	return true;
}

void CPotal::Update(float DeltaTime)
{
	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}

	CGameObject::Update(DeltaTime);
}

void CPotal::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPotal* CPotal::Clone()
{
	return new CPotal(*this);
}

void CPotal::CollisionCallbackBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		CPlayerManager::GetInst()->SetTagPotal(true);
	}
}

void CPotal::CollisionCallbackEnd(const CollisionResult& result)
{	
	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		CPlayerManager::GetInst()->SetTagPotal(false);
	}
}
