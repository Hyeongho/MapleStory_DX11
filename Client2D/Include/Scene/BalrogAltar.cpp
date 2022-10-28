#include "BalrogAltar.h"
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
}

void CBalrogAltar::LoadSound()
{
}

void CBalrogAltar::CreatePotal()
{
}
