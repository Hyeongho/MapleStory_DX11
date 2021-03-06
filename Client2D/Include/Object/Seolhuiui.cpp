#include "Seolhuiui.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Input.h"

CSeolhuiui::CSeolhuiui()
{
	SetTypeID<CSeolhuiui>();

	m_ID = 1000;
	m_NPCName = L"????";
}

CSeolhuiui::CSeolhuiui(const CSeolhuiui& obj) : CNPCManager(obj)
{
	m_Body = (CColliderPixel*)FindComponent("Body");
}

CSeolhuiui::~CSeolhuiui()
{
}

void CSeolhuiui::Start()
{
	CNPCManager::Start();
}

bool CSeolhuiui::Init()
{
	if (!CNPCManager::Init())
	{
		return false;
	}

	m_Sprite = CreateComponent<CSpriteComponent>("SeolhuiuiSprite");

	m_Body = CreateComponent<CColliderPixel>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->AddChild(m_Body);

	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	m_Sprite->SetRelativeScale(56.f, 80.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	Anim->AddAnimation(TEXT("NPC/Seolhuiui/SeolhuiuiIdle.sqc"), ANIMATION_PATH, "Idle", true);

	m_Body->SetInfo(TEXT("0800.png"));

	m_Body->SetLayerName("ColliderPixel");

	m_Body->SetPixelCollisionType(PixelCollision_Type::Alpha_Ignore);
	m_Body->SetPixelAlpha(0);

	m_Body->AddCollisionMouseCallback<CSeolhuiui>(Collision_State::Begin, this, &CSeolhuiui::CollisionCallbackBegin);
	m_Body->AddCollisionMouseCallback<CSeolhuiui>(Collision_State::End, this, &CSeolhuiui::CollisionCallbackEnd);

	return true;
}

void CSeolhuiui::Update(float DeltaTime)
{
	CNPCManager::Update(DeltaTime);
}

void CSeolhuiui::PostUpdate(float DeltaTime)
{
	CNPCManager::PostUpdate(DeltaTime);
}

CSeolhuiui* CSeolhuiui::Clone()
{
	return new CSeolhuiui(*this);
}

void CSeolhuiui::CollisionCallbackBegin(const CollisionResult& result)
{
	if (m_Action)
	{
		m_Click = false;

		return;
	}

	m_Click = true;
}

void CSeolhuiui::CollisionCallbackEnd(const CollisionResult& result)
{
	m_Click = false;
}
