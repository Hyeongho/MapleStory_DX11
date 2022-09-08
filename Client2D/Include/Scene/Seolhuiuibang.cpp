#include "Seolhuiuibang.h"
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
#include "../Scene/LoadingAnotherDoor.h"
#include "Scene/SceneManager.h"

CSeolhuiuibang::CSeolhuiuibang()
{
	SetTypeID<CSeolhuiuibang>();
}

CSeolhuiuibang::~CSeolhuiuibang()
{
}

void CSeolhuiuibang::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("Seolhuiuibang");
}

bool CSeolhuiuibang::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.6f);
	}

	CreateMap();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.3f);
	}

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	SetPlayerObject(Player);

	Player->SetWorldPos(100.f, 600.f, 0.f);

	//Player->SetRange(1400.f, 750.f, 0.f);
	Player->SetRange(Vector3(0.f, 0.f, 0.f), Vector3(1400.f, 750.f, 0.f));

	CCameraComponent* Camera = (CCameraComponent*)Player->FindComponent("Camera");

	Camera->SetTarget(Player);
	Camera->SetTargetPivot(0.5f, 0.5f, 0.f);

	Camera->SetWorldResolution(1400.f, 768.f);

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.8f);
	}

	CSeolhuiui* Seolhuiui = m_Scene->CreateGameObject<CSeolhuiui>("Seolhuiui");

	Seolhuiui->SetWorldPos(980.f, 345.f, 0.f);

	m_TalkWidget = m_Scene->GetViewport()->CreateWidgetWindow<CTalkWidget>("TalkWidget");

	m_TalkWidget->SetVisibility(false);

	m_PlayerStatus = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerStatus>("PlayerStatus");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	return true;
}

void CSeolhuiuibang::PostUpdate(float DeltaTime)
{
	if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_End)
	{
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CLoadingAnotherDoor>(false);
	}
}

void CSeolhuiuibang::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("TileMap");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	Material->SetShader("TileMapShader");
	Material->SetRenderState("AlphaBlend");
}

void CSeolhuiuibang::CreateAnimationSequence()
{
}

void CSeolhuiuibang::CreateMap()
{
	CTileMap* Back = m_Scene->LoadGameObject<CTileMap>();

	Back->Load("Seolhuiulbang/SeolhuiulbangBack.til", SCENE_PATH);

	Back->SetName("floor");

	CSharedPtr<CColliderBox2D> Box = Back->CreateComponent<CColliderBox2D>("Floor");

	Back->GetRootComponent()->AddChild(Box);

	Box->SetOffset(700.f, 198.f, 0.f);

	Box->SetExtent(700.f, 1.f);

	Box->SetCollisionProfile("Floor");

	Back->SetWorldPos(0.f, 9.f, 0.f);

}

void CSeolhuiuibang::LoadSound()
{
}
