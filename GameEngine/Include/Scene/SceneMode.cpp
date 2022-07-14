#include "SceneMode.h"
#include "../GameObject/GameObject.h"

CSceneMode::CSceneMode()
{
	SetTypeID<CSceneMode>();
}

CSceneMode::~CSceneMode()
{
}

void CSceneMode::SetPlayerObject(CGameObject* Obj)
{
	m_PlayerObject = Obj;
}

void CSceneMode::Start()
{
}

bool CSceneMode::Init()
{
	return true;
}

void CSceneMode::Update(float DeltaTime)
{
}

void CSceneMode::PostUpdate(float DeltaTime)
{
}
