#include "MainScene.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/TestMonster.h"
#include "../Object/ShadowDualBlade.h"
#include "../Object/Tauromacis.h"
#include "../Object/Potal.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"
#include "../Object/DamageFont.h"
#include "../Object/Jr_Balrog.h"
#include "../Object/Jr_BalrogAttack1Hit.h"
#include "../Object/Jr_BalrogAttack2Hit.h"
#include "../Object/Jr_BalrogAttack3Hit.h"
#include "../Object/Jr_BalrogAttack2Ball.h"

CMainScene::CMainScene()
{
	SetTypeID<CMainScene>();
}

CMainScene::~CMainScene()
{
	
}

void CMainScene::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("MainScene");

	CPlayerManager::GetInst()->SetTagPotal(false);
}

bool CMainScene::Init()
{
	RECT rc = { 0, 0, 1366, 768 };

	HWND hWnd = CEngine::GetInst()->GetWindowHandle();

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, HWND_TOPMOST, 1920, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);

	CreateMaterial();

	CreateAnimationSequence();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.3f);
	}

	CreateMap();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.6f);
	}

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	SetPlayerObject(Player);

	Player->SetWorldPos(100.f, 500.f, 0.f);

	//Player->SetRange(2000.f, 800.f, 0.f);
	Player->SetRange(Vector3(0.f, 0.f, 0.f), Vector3(2000.f, 800.f, 0.f));

	CCameraComponent* Camera = dynamic_cast<CCameraComponent*>(Player->FindComponent("Camera"));

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(2000.f, 800.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	//CJr_Balrog* ShadowDualBlade1 = m_Scene->CreateGameObject<CJr_Balrog>("Jr_Balrog");
	CShadowDualBlade* ShadowDualBlade1 = m_Scene->CreateGameObject<CShadowDualBlade>("ShadowDualBlade1");

	ShadowDualBlade1->SetWorldPos(500.f, 180.5f, 0.f);

	ShadowDualBlade1->SetRange(2000.f, 800.f, 0.f);

	/*CBalrog* Balrog = m_Scene->CreateGameObject<CBalrog>("Balrog");
	Balrog->SetWorldPos(700.f, 400.f, 0.f);*/

	CPotal* Potal = m_Scene->CreateGameObject<CPotal>("Potal");

	Potal->SetRelativePos(1800.f, 150, 0.f);

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.9f);
	}

	//CDamageFont* DamageFont = m_Scene->CreatePrototype<CDamageFont>("DamagrFont");

	return true;
}

void CMainScene::PostUpdate(float DeltaTime)
{
	
}

void CMainScene::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("TileMap");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	Material->SetShader("TileMapShader");
	Material->SetRenderState("AlphaBlend");
}

void CMainScene::CreateAnimationSequence()
{
	/*m_Scene->GetResource()->LoadSequence2D("PlayerIdle.sqc");
	m_Scene->GetResource()->LoadSequence2D("PlayerRun.sqc");*/
}

void CMainScene::CreateMap()
{
	CTileMap* Floor1 = m_Scene->LoadGameObject<CTileMap>();

	//TileMap->Load("Tutorial/Floor1.til", SCENE_PATH);
	Floor1->Load("Tutorial/Floor1.til", SCENE_PATH);

	Floor1->SetName("floor");

	CSharedPtr<CColliderBox2D> Box = Floor1->CreateComponent<CColliderBox2D>("Floor");

	Floor1->GetRootComponent()->AddChild(Box);

	Box->SetPivot(0.f, 1.0f, 0.f);

	Box->SetOffset(2000.f, 130.f, 0.f);

	Box->SetExtent(2000.f, 20.f);

	Box->SetCollisionProfile("Floor");

	Box->AddCollisionCallback<CMainScene>(Collision_State::Begin, this, &CMainScene::CollisionBeginCallback);

	Floor1->SetWorldPos(0.f, 0.f, 0.f);

	CTileMap* Wall1 = m_Scene->LoadGameObject<CTileMap>();

	//TileMap->Load("Tutorial/Floor1.til", SCENE_PATH);
	Wall1->Load("Tutorial/Wall1.til", SCENE_PATH);

	Wall1->SetName("Wall1");

	Floor1->SetWorldPos(0.f, 0.f, 0.f);
}

void CMainScene::LoadSound()
{
}

void CMainScene::CollisionBeginCallback(const CollisionResult& Result)
{
	if (Result.Dest->GetCollisionProfile()->Channel == Collision_Channel::PlayerBottom)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(Result.Dest->GetGameObject());

		if (!Player)
		{
			return;
		}

		Player->SetGround(true);

		Vector3 DestPos = Result.Dest->GetWorldPos() + Result.Dest->GetOffset();
		Vector3 DestScale = Result.Dest->GetWorldScale();

		Vector3 SrcOffSet = Result.Src->GetOffset();
		Vector3 DestOffSet = Result.Dest->GetOffset();

		Vector3 SrcPos = Result.Src->GetWorldPos() + Result.Src->GetOffset();
		Vector3 SrcScale = Result.Src->GetWorldScale();

		float Len = abs(DestPos.y - SrcPos.y);
		float Value = (DestScale.y / 2.f + SrcScale.y / 2.f) - Len;

		DestPos = Player->GetWorldPos();
		DestPos.y += Value;

		Player->SetWorldPos(DestPos);
	}	
}

void CMainScene::CollisionEndCallback(const CollisionResult& Result)
{
}

