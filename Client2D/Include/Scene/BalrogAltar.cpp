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
#include "../Object/BodyAttack1Hit.h"
#include "../Object/BodyAttack2Hit.h"
#include "../Object/BodyAttack3Hit.h"
#include "../Object/BodyAttack4Hit.h"
#include "../Object/LeftAttack1Hit.h"
#include "../Object/LeftAttack2Hit.h"
#include "../Object/RightAttack1Hit.h"
#include "../Object/RightAttack2Hit.h"
#include "../Object/RightAttack3Hit.h"

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

	CCameraComponent* Camera = dynamic_cast<CCameraComponent*>(Player->FindComponent("Camera"));

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(1366.f, 768.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.6f);
	}

	CBalrog* Balrog = m_Scene->CreateGameObject<CBalrog>("Balrog");
	Balrog->SetWorldPos(700.f, 400.f, 0.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	m_BossStatus = m_Scene->GetViewport()->CreateWidgetWindow<CBossStatus>("BossStatus");

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	CBodyAttack1Hit* BodyAttack1Hit = m_Scene->CreatePrototype<CBodyAttack1Hit>("BodyAttack1Hit");
	CBodyAttack2Hit* BodyAttack2Hit = m_Scene->CreatePrototype<CBodyAttack2Hit>("BodyAttack2Hit");
	CBodyAttack3Hit* BodyAttack3Hit = m_Scene->CreatePrototype<CBodyAttack3Hit>("BodyAttack3Hit");
	CBodyAttack4Hit* BodyAttack4Hit = m_Scene->CreatePrototype<CBodyAttack4Hit>("BodyAttack4Hit");

	CLeftAttack1Hit* LeftAttack1Hit = m_Scene->CreatePrototype<CLeftAttack1Hit>("LeftAttack1Hit");
	CLeftAttack2Hit* LeftAttack2Hit = m_Scene->CreatePrototype<CLeftAttack2Hit>("LeftAttack2Hit");

	CRightAttack1Hit* RightAttack1Hit = m_Scene->CreatePrototype<CRightAttack1Hit>("RightAttack1Hit");
	CRightAttack2Hit* RightAttack2Hit = m_Scene->CreatePrototype<CRightAttack2Hit>("RightAttack2Hit");
	CRightAttack3Hit* RightAttack3Hit = m_Scene->CreatePrototype<CRightAttack3Hit>("RightAttack3Hit");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.9f);
	}

	return true;
}

void CBalrogAltar::PostUpdate(float DeltaTime)
{
	CBalrog* Balrog = dynamic_cast<CBalrog*>(m_Scene->FindObject("Balrog"));

	if (!Balrog)
	{
		return;
	}

	if (Balrog->GetState() == EMonster_State::Die)
	{
		if (!m_Clear)
		{
			m_Clear = m_Scene->GetViewport()->CreateWidgetWindow<CClearFWidget>("ClearF");
		}
	}
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

	Box->SetOffset(683.f, 98.f, 0.f);

	Box->SetExtent(600.f, 20.f);

	Box->SetCollisionProfile("Floor");

	Box->AddCollisionCallback<CBalrogAltar>(Collision_State::Begin, this, &CBalrogAltar::CollisionBeginCallback);
}

void CBalrogAltar::LoadSound()
{
}

void CBalrogAltar::CreatePotal()
{
}

void CBalrogAltar::CollisionBeginCallback(const CollisionResult& Result)
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

void CBalrogAltar::CollisionEndCallback(const CollisionResult& Result)
{
}
