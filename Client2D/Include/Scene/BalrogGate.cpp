#include "BalrogGate.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/Potal.h"
#include "../Object/HongA.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"
#include "Scene/SceneManager.h"

CBalrogGate::CBalrogGate()
{
}

CBalrogGate::~CBalrogGate()
{
}

void CBalrogGate::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("BalrogGate");

	CPlayerManager::GetInst()->SetTagPotal(false);
}

bool CBalrogGate::Init()
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

	CCameraComponent* Camera = dynamic_cast<CCameraComponent*>(Player->FindComponent("Camera"));

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(1980.f, 960.f);

	CHongA* HongA = m_Scene->CreateGameObject<CHongA>("HongA");

	HongA->SetWorldPos(1600.f, 246.f, 0.f);

	m_TalkWidget = m_Scene->GetViewport()->CreateWidgetWindow<CTalkWidget>("TalkWidget");

	m_TalkWidget->SetVisibility(false);

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.9f);
	}

	return true;
}

void CBalrogGate::PostUpdate(float DeltaTime)
{
}

void CBalrogGate::CreateMaterial()
{
}

void CBalrogGate::CreateAnimationSequence()
{
}

void CBalrogGate::CreateMap()
{
	CTileMap* Back = m_Scene->LoadGameObject<CTileMap>();

	Back->Load("Balrog_Gate/BalrogGate.til", SCENE_PATH);

	Back->SetName("floor");

	CSharedPtr<CColliderBox2D> Box = Back->CreateComponent<CColliderBox2D>("Floor");

	Back->GetRootComponent()->AddChild(Box);

	Box->SetOffset(960.f, 185.f, 0.f);

	Box->SetExtent(1072.f, 20.f);

	Box->SetCollisionProfile("Floor");

	Box->AddCollisionCallback<CBalrogGate>(Collision_State::Begin, this, &CBalrogGate::CollisionBeginCallback);
}

void CBalrogGate::LoadSound()
{
}

void CBalrogGate::CreatePotal()
{
}

void CBalrogGate::CollisionBeginCallback(const CollisionResult& Result)
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

void CBalrogGate::CollisionEndCallback(const CollisionResult& Result)
{
}
