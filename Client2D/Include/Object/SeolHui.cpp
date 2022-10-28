#include "SeolHui.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/SceneManager.h"
#include "../Scene/LoadingAnotherDoor.h"
#include "Input.h"

CSeolHui::CSeolHui()
{
	SetTypeID<CSeolHui>();

	m_ID = 1000;
	m_NPCName = L"¼³Èñ";
}

CSeolHui::CSeolHui(const CSeolHui& obj) : CNPCManager(obj)
{
	m_Body = (CColliderPixel*)FindComponent("Body");
}

CSeolHui::~CSeolHui()
{
}

void CSeolHui::Start()
{
	CNPCManager::Start();
}

bool CSeolHui::Init()
{
	if (!CNPCManager::Init())
	{
		return false;
	}

	m_Sprite = CreateComponent<CSpriteComponent>("SeolHuiSprite");

	m_Body = CreateComponent<CColliderPixel>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->AddChild(m_Body);

	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	m_Sprite->SetRelativeScale(56.f, 80.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	Anim->AddAnimation(TEXT("NPC/SeolHui/SeolHuiIdle.sqc"), ANIMATION_PATH, "Idle", true);

	m_Body->SetInfo(TEXT("0800.png"));

	m_Body->SetLayerName("ColliderPixel");

	m_Body->SetPixelCollisionType(PixelCollision_Type::Alpha_Ignore);
	m_Body->SetPixelAlpha(0);

	m_Body->AddCollisionMouseCallback<CSeolHui>(Collision_State::Begin, this, &CSeolHui::CollisionCallbackBegin);
	m_Body->AddCollisionMouseCallback<CSeolHui>(Collision_State::End, this, &CSeolHui::CollisionCallbackEnd);

	return true;
}

void CSeolHui::Update(float DeltaTime)
{
	CNPCManager::Update(DeltaTime);
}

void CSeolHui::PostUpdate(float DeltaTime)
{
	CNPCManager::PostUpdate(DeltaTime);

	if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_End)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CLoadingAnotherDoor>(false);
	}
}

CSeolHui* CSeolHui::Clone()
{
	return new CSeolHui(*this);
}

void CSeolHui::CollisionCallbackBegin(const CollisionResult& result)
{
	if (m_Action)
	{
		m_Click = false;

		return;
	}

	m_Click = true;
}

void CSeolHui::CollisionCallbackEnd(const CollisionResult& result)
{
	m_Click = false;
}
