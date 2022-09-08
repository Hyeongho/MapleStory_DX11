#include "EntranceToTemple.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/TestMonster.h"
#include "../Object/Tauromacis.h"
#include "../Object/Taurospear.h"
#include "../Object/Potal.h"
#include "../Object/Seolhuiui.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"

CEntranceToTemple::CEntranceToTemple()
{
	SetTypeID<CEntranceToTemple>();
}

CEntranceToTemple::~CEntranceToTemple()
{
}

void CEntranceToTemple::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("EntranceToTemple");
}

bool CEntranceToTemple::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.2f);
	}

	CreateMap();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.4f);
	}

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	SetPlayerObject(Player);

	Player->SetWorldPos(100.f, 600.f, 0.f);

	//Player->SetRange(1400.f, 750.f, 0.f);
	Player->SetRange(Vector3(0.f, 0.f, 0.f), Vector3(2144.f, 750.f, 0.f));

	CCameraComponent* Camera = (CCameraComponent*)Player->FindComponent("Camera");

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(2144.f, 999.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.6f);
	}

	CTauromacis* Tauromacis = m_Scene->CreateGameObject<CTauromacis>("Tauromacis");

	Tauromacis->SetWorldPos(600.f, 250.f, 1.f);

	Tauromacis->SetRange(2144.f, 750.f, 0.f);

	/*CTaurospear* Taurospear = m_Scene->CreateGameObject<CTaurospear>("Taurospear");

	Taurospear->SetWorldPos(600.f, 250.f, 1.f);

	Taurospear->SetRange(2144.f, 750.f, 0.f);*/

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	m_TalkWidget = m_Scene->GetViewport()->CreateWidgetWindow<CTalkWidget>("TalkWidget");

	m_TalkWidget->SetVisibility(false);

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	return true;
}

void CEntranceToTemple::PostUpdate(float DeltaTime)
{
}

void CEntranceToTemple::CreateMaterial()
{
}

void CEntranceToTemple::CreateAnimationSequence()
{
}

void CEntranceToTemple::CreateMap()
{
	CTileMap* Back = m_Scene->LoadGameObject<CTileMap>();

	Back->Load("EntranceToTemple/EntranceToTemple.til", SCENE_PATH);

	Back->SetName("floor");

	CSharedPtr<CColliderBox2D> Box = Back->CreateComponent<CColliderBox2D>("Floor");

	Back->GetRootComponent()->AddChild(Box);

	Box->SetOffset(1072.f, 190.f, 0.f);

	Box->SetExtent(1072.f, 1.f);

	Box->SetCollisionProfile("Floor");
}

void CEntranceToTemple::LoadSound()
{
}
