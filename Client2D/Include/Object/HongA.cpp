#include "HongA.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/SceneManager.h"
#include "../Scene/LoadingAnotherDoor.h"
#include "../Scene/LoadingBalrogAltar.h"
#include "Input.h"

CHongA::CHongA()
{
	SetTypeID<CHongA>();

	m_ID = 1001;
	m_NPCName = L"È«¾Æ";
}

CHongA::CHongA(const CHongA& obj)
{
	m_Body = dynamic_cast<CColliderPixel*>(FindComponent("Body"));
}

CHongA::~CHongA()
{
}

void CHongA::Start()
{
	CNPCManager::Start();
}

bool CHongA::Init()
{
	if (!CNPCManager::Init())
	{
		return false;
	}

	m_Sprite = CreateComponent<CSpriteComponent>("CHongASprite");

	m_Body = CreateComponent<CColliderPixel>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->AddChild(m_Body);

	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	m_Sprite->SetRelativeScale(64.f, 82.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "HongA", TEXT("NPC/HongA/stand.0.png"));

	m_Body->SetInfo(TEXT("NPC/HongA/stand.0.png"));

	m_Body->SetLayerName("ColliderPixel");

	m_Body->SetPixelCollisionType(PixelCollision_Type::Alpha_Ignore);
	m_Body->SetPixelAlpha(0);

	m_Body->AddCollisionMouseCallback<CHongA>(Collision_State::Begin, this, &CHongA::CollisionCallbackBegin);
	m_Body->AddCollisionMouseCallback<CHongA>(Collision_State::End, this, &CHongA::CollisionCallbackEnd);

	return true;
}

void CHongA::Update(float DeltaTime)
{
	CNPCManager::Update(DeltaTime);
}

void CHongA::PostUpdate(float DeltaTime)
{
	CNPCManager::PostUpdate(DeltaTime);

	if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_End)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CLoadingBalrogAltar>(false);
	}
}

CHongA* CHongA::Clone()
{
	return new CHongA(*this);
}

void CHongA::CollisionCallbackBegin(const CollisionResult& result)
{
	if (m_Action)
	{
		m_Click = false;

		return;
	}

	m_Click = true;
}

void CHongA::CollisionCallbackEnd(const CollisionResult& result)
{
	m_Click = false;
}
