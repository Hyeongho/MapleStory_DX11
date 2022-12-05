#include "EntranceToTemple.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/MonsterManager.h"
#include "../Object/Tauromacis.h"
#include "../Object/Taurospear.h"
#include "../Object/Potal.h"
#include "../Object/SeolHui.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"
#include "../Object/TauromacisHitEffect.h"

CEntranceToTemple::CEntranceToTemple() : m_MobCount(0), m_TotalMobCount(30), m_SpawnTime(4.f)
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

	CPlayerManager::GetInst()->SetTagPotal(false);
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

	CCameraComponent* Camera = dynamic_cast<CCameraComponent*>(Player->FindComponent("Camera"));

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(2144.f, 999.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.6f);
	}

	CTauromacisHitEffect* TauromacisHitEffect = m_Scene->CreatePrototype<CTauromacisHitEffect>("TauromacisHitEffect");

	CTauromacis* Tauromacis = m_Scene->CreateGameObject<CTauromacis>("Tauromacis");

	Tauromacis->SetWorldPos(600.f, 250.f, 1.f);

	Tauromacis->SetRange(2144.f, 750.f, 0.f);

	m_MonsterList.push_back(Tauromacis);

	CTaurospear* Taurospear = m_Scene->CreateGameObject<CTaurospear>("Taurospear");

	Taurospear->SetWorldPos(800.f, 250.f, 1.f);

	Taurospear->SetRange(2144.f, 750.f, 0.f);

	m_MonsterList.push_back(Taurospear);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	CPotal* Potal = m_Scene->CreateGameObject<CPotal>("Potal");

	Potal->SetRelativePos(2000.f, 190.f, 0.f);

	m_TalkWidget = m_Scene->GetViewport()->CreateWidgetWindow<CTalkWidget>("TalkWidget");

	m_TalkWidget->SetVisibility(false);

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");
	m_Quset = m_Scene->GetViewport()->CreateWidgetWindow<CQuesetWidget>("QuesetWidget");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.9f);
	}

	return true;
}

void CEntranceToTemple::PostUpdate(float DeltaTime)
{
	MonsterSpawn(DeltaTime);

	auto iter = m_MonsterList.begin();
	auto iterEnd = m_MonsterList.end();

	for ( ; iter != iterEnd; )
	{
		if ((*iter)->GetState() == EMonster_State::Die)
		{
			iter = m_MonsterList.erase(iter);
			iterEnd = m_MonsterList.end();

			m_MobCount++;			

			if (m_Quset)
			{
				std::string str = std::to_string(m_MobCount) + " / " + std::to_string(m_TotalMobCount);

				m_Quset->SetText(str);
			}

			continue;
		}

		else
		{
			iter++;
		}
	}

	if (m_MobCount >= 30)
	{
		if (!m_MonsterList.empty())
		{
			for (; iter != iterEnd; iter++)
			{
				if (!(*iter)->IsActive())
				{
					(*iter)->Destroy();
				}
			}

			m_MonsterList.clear();
		}

		if (!m_Scene->FindObject("Potal"))
		{
			CPotal* Potal = m_Scene->CreateGameObject<CPotal>("Potal");

			Potal->SetRelativePos(2000.f, 190.f, 0.f);
		}
	}
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

	Box->SetOffset(1072.f, 170.f, 0.f);

	Box->SetExtent(1072.f, 20.f);

	Box->SetCollisionProfile("Floor");

	Box->AddCollisionCallback<CEntranceToTemple>(Collision_State::Begin, this, &CEntranceToTemple::CollisionBeginCallback);
}

void CEntranceToTemple::LoadSound()
{
}

void CEntranceToTemple::CreatePotal()
{
}

void CEntranceToTemple::MonsterSpawn(float DeltaTime)
{
	if (m_MonsterList.size() <= 16)
	{
		m_SpawnTime -= DeltaTime;

		if (m_SpawnTime < 0)
		{
			float PosX = static_cast<float>(rand() % 2144);

			CTauromacis* Tauromacis = m_Scene->CreateGameObject<CTauromacis>("Tauromacis");

			Tauromacis->SetWorldPos(PosX, 250.f, 1.f);

			Tauromacis->SetRange(2144.f, 750.f, 0.f);

			m_MonsterList.push_back(Tauromacis);

			PosX = static_cast<float>(rand() % 2144);

			Tauromacis = m_Scene->CreateGameObject<CTauromacis>("Tauromacis");

			Tauromacis->SetWorldPos(PosX, 250.f, 1.f);

			Tauromacis->SetRange(2144.f, 750.f, 0.f);

			m_MonsterList.push_back(Tauromacis);

			PosX = static_cast<float>(rand() % 2144);

			CTaurospear* Taurospear = m_Scene->CreateGameObject<CTaurospear>("Taurospear");

			Taurospear->SetWorldPos(PosX, 250.f, 1.f);

			Taurospear->SetRange(2144.f, 750.f, 0.f);

			m_MonsterList.push_back(Taurospear);

			PosX = static_cast<float>(rand() % 2144);

			Taurospear = m_Scene->CreateGameObject<CTaurospear>("Taurospear");

			Taurospear->SetWorldPos(PosX, 250.f, 1.f);

			Taurospear->SetRange(2144.f, 750.f, 0.f);

			m_MonsterList.push_back(Taurospear);

			m_SpawnTime = 4.f;
		}
	}
}

void CEntranceToTemple::CollisionBeginCallback(const CollisionResult& Result)
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

void CEntranceToTemple::CollisionEndCallback(const CollisionResult& Result)
{
}
