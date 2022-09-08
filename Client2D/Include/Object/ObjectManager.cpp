#include "ObjectManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/SceneManager.h"
#include "Component/CameraComponent.h"
#include "Component/TileMapComponent.h"
#include "Player2D.h"
#include "../Widget/Fade.h"
#include "../ClientManager.h"
#include "PlayerManager.h"
#include "../Scene/LoadingSeolhuiui.h"

CObjectManager::CObjectManager() : m_CharacterInfo{}, m_PhysicsSimulate(false), m_GravityAccel(10.f), m_IsGround(true), m_FallTime(0.f),
	m_Jump(false), m_FallStartY(0.f), m_JumpVelocity(0.f), m_FloorCheck(false), m_SideWallCheck(false), m_Dir(1.0f)
{
}

CObjectManager::CObjectManager(const CObjectManager& obj) : CGameObject(obj)
{
	m_CharacterInfo = obj.m_CharacterInfo;

	//m_Direction = obj.m_Direction;
	m_Dir = obj.m_Dir;
	m_PrevPos.y = -1.f;
	m_FloorCheck = obj.m_FloorCheck;
	m_PhysicsSimulate = obj.m_PhysicsSimulate;
	m_IsGround = obj.m_IsGround;
	m_FallTime = obj.m_FallTime;
	m_FallStartY = obj.m_FallStartY;
	m_Jump = obj.m_Jump;
	m_JumpVelocity = obj.m_JumpVelocity;
	m_GravityAccel = obj.m_GravityAccel;
}

CObjectManager::~CObjectManager()
{
	
}

void CObjectManager::Start()
{
	CGameObject::Start();

	m_FallStartY = GetWorldPos().y;
	m_FallStartX = GetWorldPos().x;
}

bool CObjectManager::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	return true;
}

void CObjectManager::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CObjectManager::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	CFade* Fade = (CFade*)m_Scene->GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

	if (CClientManager::GetInst()->GetFade())
	{
		if (!Fade->GetVisibility())
		{
			Fade->SetVisibility(true);
			CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_Start);
		}
	}
}

CObjectManager* CObjectManager::Clone()
{
	return nullptr;
}

float CObjectManager::SetDamage(float Damage)
{
	//Damage = CGameObject::SetDamage(Damage);

	m_CharacterInfo.HP -= (int)Damage;

	return Damage;
}

void CObjectManager::SetCharacterInfo(const std::string& name)
{
	m_CharacterInfo = CClientManager::GetInst()->FindData(name);
}

