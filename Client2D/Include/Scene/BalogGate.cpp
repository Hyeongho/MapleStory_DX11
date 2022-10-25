#include "BalogGate.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/Potal.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "../ClientManager.h"
#include "../Object/PlayerManager.h"
#include "Scene/SceneManager.h"

CBalogGate::CBalogGate()
{
}

CBalogGate::~CBalogGate()
{
}

void CBalogGate::Start()
{
	CClientManager::GetInst()->SetFadeState(EFade_State::FadeIn_Start);
	CClientManager::GetInst()->SetFade(false);
	CPlayerManager::GetInst()->SetCurrentScene("BalogGate");

	CPlayerManager::GetInst()->SetTagPotal(false);
}

bool CBalogGate::Init()
{
	return true;
}

void CBalogGate::PostUpdate(float DeltaTime)
{
}

void CBalogGate::CreateMaterial()
{
}

void CBalogGate::CreateAnimationSequence()
{
}

void CBalogGate::CreateMap()
{
	CTileMap* Back = m_Scene->LoadGameObject<CTileMap>();

	Back->Load("Balog_Gate/BalogGate.til", SCENE_PATH);

	Back->SetName("floor");

	CSharedPtr<CColliderBox2D> Box = Back->CreateComponent<CColliderBox2D>("Floor");

	Back->GetRootComponent()->AddChild(Box);

	Box->SetOffset(1072.f, 190.f, 0.f);

	Box->SetExtent(1072.f, 1.f);

	Box->SetCollisionProfile("Floor");
}

void CBalogGate::LoadSound()
{
}

void CBalogGate::CreatePotal()
{
}
