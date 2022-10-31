#include "BalrogAltar.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/Potal.h"
#include "../Object/HongA.h"
#include "../Object/Balrog.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"
#include "Scene/SceneManager.h"

CBalrogAltar::CBalrogAltar()
{
}

CBalrogAltar::~CBalrogAltar()
{
}

void CBalrogAltar::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("BalrogAltar");

	CPlayerManager::GetInst()->SetTagPotal(false);
}

bool CBalrogAltar::Init()
{
	CreateMap();

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
	Player->SetRange(Vector3(83.f, 0.f, 0.f), Vector3(1366.f - 83.f, 900.f, 0.f));

	CCameraComponent* Camera = (CCameraComponent*)Player->FindComponent("Camera");

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(1366.f, 768.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.6f);
	}

	CBalrog* Balrog = m_Scene->CreateGameObject<CBalrog>("Balrog");
	//Balrog->SetWorldPos(700.f, 400.f, 0.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.9f);
	}

	return true;
}

void CBalrogAltar::PostUpdate(float DeltaTime)
{
}

void CBalrogAltar::CreateMaterial()
{
}

void CBalrogAltar::CreateAnimationSequence()
{
}

void CBalrogAltar::CreateMap()
{
	CTileMap* BalrogAltarBack = m_Scene->LoadGameObject<CTileMap>();

	BalrogAltarBack->Load("Balrog_Altar/BalrogAltar_Back.til", SCENE_PATH);

	BalrogAltarBack->SetName("Back");

	BalrogAltarBack->AddWorldPos(83.f, 0.f, 0.f);

	CTileMap* Floor = m_Scene->LoadGameObject<CTileMap>();

	Floor->Load("Balrog_Altar/BalrogAltar_Floor.til", SCENE_PATH);

	Floor->SetName("Floor");

	Floor->AddWorldPos(83.f, -24.f, 0.f);

	CSharedPtr<CColliderBox2D> Box = Floor->CreateComponent<CColliderBox2D>("Floor");

	Floor->GetRootComponent()->AddChild(Box);

	Floor->GetRootComponent()->SetLayerName("BalrogFloor");

	Box->SetOffset(683.f, 118.f, 0.f);

	Box->SetExtent(600.f, 1.f);

	Box->SetCollisionProfile("Floor");
}

void CBalrogAltar::LoadSound()
{
}

void CBalrogAltar::CreatePotal()
{
}
