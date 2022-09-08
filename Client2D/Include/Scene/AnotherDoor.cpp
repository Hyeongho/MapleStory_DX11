#include "AnotherDoor.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/TestMonster.h"
#include "../Object/ShadowDualBlade.h"
#include "../Object/Potal.h"
#include "../Object/Seolhuiui.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"
#include "../Scene/LoadingEToTemple.h"
#include "Scene/SceneManager.h"

CAnotherDoor::CAnotherDoor()
{
	SetTypeID<CAnotherDoor>();
}

CAnotherDoor::~CAnotherDoor()
{
}

void CAnotherDoor::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("AnotherDoor");
}

bool CAnotherDoor::Init()
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

	Player->SetWorldPos(200.f, 600.f, 0.f);

	Player->SetRange(Vector3(158.f, 0.f, 0.f), Vector3(1366.f - 158.f, 768.f, 0.f));

	CCameraComponent* Camera = (CCameraComponent*)Player->FindComponent("Camera");

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(1366.f, 768.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.6f);
	}

	LoadSound();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	CPotal* Potal = m_Scene->CreateGameObject<CPotal>("Potal");

	Potal->SetRelativePos(916.f, 262.f, 0.f);

	m_TalkWidget = m_Scene->GetViewport()->CreateWidgetWindow<CTalkWidget>("TalkWidget");

	m_TalkWidget->SetVisibility(false);

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	return true;
}

void CAnotherDoor::PostUpdate(float DeltaTime)
{
	/*if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_End)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CLoadingEToTemple>(false);
	}*/
}

void CAnotherDoor::CreateMaterial()
{
}

void CAnotherDoor::CreateAnimationSequence()
{
}

void CAnotherDoor::CreateMap()
{
	CTileMap* Back = m_Scene->LoadGameObject<CTileMap>();

	Back->Load("AnotherDoor/AnotherDoor.til", SCENE_PATH);

	Back->SetName("floor");

	CSharedPtr<CColliderBox2D> Box = Back->CreateComponent<CColliderBox2D>("Floor");

	Back->GetRootComponent()->AddChild(Box);

	Box->SetOffset(528.5f, 265.5f, 0.f);

	Box->SetExtent(1049.f, 1.f);

	Box->SetCollisionProfile("Floor");

	//Back->SetWorldPos(0.f, 180.f, 0.f);
}

void CAnotherDoor::LoadSound()
{
	m_Scene->GetResource()->SoundStop("secretFlower");

	m_Scene->GetResource()->SoundPlay("EvilEyes");
}
