#include "SeolHuibang.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/TestMonster.h"
#include "../Object/ShadowDualBlade.h"
#include "../Object/Potal.h"
#include "../Object/SeolHui.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"
#include "../Scene/LoadingAnotherDoor.h"

CSeolHuibang::CSeolHuibang()
{
	SetTypeID<CSeolHuibang>();
}

CSeolHuibang::~CSeolHuibang()
{
}

void CSeolHuibang::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("SeolHuibang");

	CPlayerManager::GetInst()->SetTagPotal(false);
}

bool CSeolHuibang::Init()
{
	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.f);
	}

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

	Player->SetWorldPos(100.f, 600.f, 0.f);

	//Player->SetRange(1400.f, 750.f, 0.f);
	Player->SetRange(Vector3(0.f, 0.f, 0.f), Vector3(1400.f, 750.f, 0.f));

	CCameraComponent* Camera = dynamic_cast<CCameraComponent*>(Player->FindComponent("Camera"));

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(1400.f, 768.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	CSeolHui* SeolHui = m_Scene->CreateGameObject<CSeolHui>("SeolHui");

	SeolHui->SetWorldPos(980.f, 345.f, 0.f);

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

void CSeolHuibang::PostUpdate(float DeltaTime)
{
	/*if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_End)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CLoadingAnotherDoor>(false);
	}*/
}

void CSeolHuibang::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("TileMap");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	Material->SetShader("TileMapShader");
	Material->SetRenderState("AlphaBlend");
}

void CSeolHuibang::CreateAnimationSequence()
{
}

void CSeolHuibang::CreateMap()
{
	CTileMap* Back = m_Scene->LoadGameObject<CTileMap>();

	Back->Load("SeolHuibang/SeolHuibangBack.til", SCENE_PATH);

	Back->SetName("floor");

	CSharedPtr<CColliderBox2D> Box = Back->CreateComponent<CColliderBox2D>("Floor");

	Back->GetRootComponent()->AddChild(Box);

	Box->SetOffset(700.f, 178.f, 0.f);

	Box->SetExtent(700.f, 20.f);

	Box->AddCollisionCallback<CSeolHuibang>(Collision_State::Begin, this, &CSeolHuibang::CollisionBeginCallback);

	Box->SetCollisionProfile("Floor");

	Back->SetWorldPos(0.f, 9.f, 0.f);

}

void CSeolHuibang::LoadSound()
{
}

void CSeolHuibang::CollisionBeginCallback(const CollisionResult& Result)
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

void CSeolHuibang::CollisionEndCallback(const CollisionResult& Result)
{
}
