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

	//// 중력을 적용한다.
	//if (!m_IsGround && m_PhysicsSimulate)
	//{
	//	// 떨어지는 시간을 누적시켜준다.
	//	m_FallTime += DeltaTime * m_GravityAccel;

	//	// 9.8 m/s^2
	//	// t초 후 y값
	//	// V: 속도	A: 가속도	G: 중력
	//	// y = V * A - 0.5f * G * T * T
	//	// 0 = -0.5GA^2 VA - y
	//	// (*b +- 루트(b^2 - 4ac)) / 2a
	//	float Velocity = 0.f;

	//	CPlayer2D* Player = (CPlayer2D*)m_Scene->GetPlayerObject();

	//	Vector3 Pos = GetWorldPos();
	//	Vector3 Pivot = GetPivot();
	//	Vector3 Scale = GetWorldScale();

	//	if (!Player)
	//	{
	//		return;
	//	}

	//	if (m_Jump)
	//	{
	//		Velocity = m_JumpVelocity * m_FallTime;

	//		if (Player->GetPlayerState() == EPlayer_State::Walk)
	//		{
	//			m_FallStartX = Pos.x;
	//		}

	//		else
	//		{
	//			m_FallStartX = 0.f;
	//		}
	//	}

	//	Pos.y = m_FallStartY + (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);

	//	//Pos.x = m_FallStartX - (Velocity + 0.5f * GRAVITY * m_FallTime * m_FallTime);

	//	if (Player->GetPlayerState() == EPlayer_State::Walk)
	//	{
	//		Pos.x += 300.f * DeltaTime * m_Dir;
	//	}

	//	SetWorldPos(Pos);
	//}
}

void CObjectManager::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	CFade* Fade = (CFade*)m_Scene->GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

	if (CClientManager::GetInst()->GetFade())
	{
		CClientManager::GetInst()->SetFade(false);

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

