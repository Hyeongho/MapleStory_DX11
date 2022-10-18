#include "StartScene.h"
#include "Engine.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "../Object/Player2D.h"
#include "../Object/TestMonster.h"
#include "../Object/ShadowDualBlade.h"
#include "../Object/Potal.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

void CStartScene::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	LoadSound();
}

bool CStartScene::Init()
{
	RECT rc = { 0, 0, 1024, 768 };

	HWND hWnd = CEngine::GetInst()->GetWindowHandle();

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, HWND_TOPMOST, 1920, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);

	CreateMaterial();

	//CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	m_StartWidget = m_Scene->GetViewport()->CreateWidgetWindow<CStartWidget>("StartWidget");
	m_Fade = m_Scene->GetViewport()->CreateWidgetWindow<CFade>("FadeWidget");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.9f);
	}

	return true;
}

void CStartScene::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("TileMap");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	Material->SetShader("TileMapShader");
	Material->SetRenderState("AlphaBlend");
}

void CStartScene::CreateAnimationSequence()
{
}

void CStartScene::LoadSound()
{
	m_Scene->GetResource()->SoundPlay("secretFlower");
}
