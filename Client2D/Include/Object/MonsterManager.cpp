#include "MonsterManager.h"
#include "Player2D.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"

CMonsterManager::CMonsterManager() : m_State(EMonster_State::Idle), m_Flip(true), m_Trace(false), m_TraceTime(0.f), m_Speed(0.f), m_Stop(false), m_ActiveTime(0.f), m_RandActive(0.f), m_Attack(false), 
	m_Hurt(false)
{
	SetTypeID<CMonsterManager>();
}

CMonsterManager::CMonsterManager(const CMonsterManager& obj) : CObjectManager(obj)
{
}

CMonsterManager::~CMonsterManager()
{
}

void CMonsterManager::Start()
{
	CObjectManager::Start();
}

bool CMonsterManager::Init()
{
	CObjectManager::Init();

	m_Player = (CPlayer2D*)m_Scene->GetPlayerObject();

	return true;
}

void CMonsterManager::Update(float DeltaTime)
{
	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}

	CObjectManager::Update(DeltaTime);

	if (m_CharacterInfo.HP <= 0)
	{
		m_Stop = true;
	}

	CPlayer2D* Player = (CPlayer2D*)m_Scene->GetPlayerObject();

	Vector3 Range = GetRange();

	Vector3 Pos = GetRelativePos();

	CColliderBox2D* Body = (CColliderBox2D*)FindComponent("Body");

	if (Body)
	{
		Box2DInfo Info = Body->GetInfo();

		if (Pos.x - (Info.Length.x) < 0.f)
		{
			Pos.x = (Info.Length.x);
		}

		if (Info.Length.x + Pos.x > Range.x)
		{
			Pos.x = Range.x - Info.Length.x;
		}

		SetWorldPos(Pos);
	}

	m_ActiveTime += DeltaTime;

	switch (m_State)
	{
	case EMonster_State::Idle:
	case EMonster_State::Move:

		if (m_ActiveTime > m_RandActive)
		{
			m_ActiveTime = 0.f;

			m_IsMove = rand() % 2;

			if (m_IsMove)
			{
				m_Flip = (bool)(rand() % 2);

				m_State = EMonster_State::Move;
			}

			else
			{
				m_State = EMonster_State::Idle;
			}

			m_RandActive = (float)(rand() % 2);
		}

		break;
	default:
		break;
	}

}

void CMonsterManager::PostUpdate(float DeltaTime)
{
	CObjectManager::PostUpdate(DeltaTime);

	if ((CClientManager::GetInst()->GetFadeState() != EFade_State::Normal) || (CClientManager::GetInst()->GetFade()))
	{
		return;
	}

	switch (m_State)
	{
	case EMonster_State::Idle:
		AIIdle(DeltaTime);
		break;

	case EMonster_State::Move:
		AIMove(DeltaTime);
		break;

	case EMonster_State::Trace:
		AITrace(DeltaTime);
		break;

	case EMonster_State::Attack:
		AIAttack(DeltaTime);
		break;

	case EMonster_State::Die:
		AIDeath(DeltaTime);
		break;
	}
}

CMonsterManager* CMonsterManager::Clone()
{
	return new CMonsterManager(*this);
}

void CMonsterManager::AIIdle(float DeltaTime)
{
}

void CMonsterManager::AIMove(float DeltaTime)
{

}

void CMonsterManager::AITrace(float DeltaTime)
{
	CPlayer2D* Player = (CPlayer2D*)m_Scene->GetPlayerObject();

	Vector3 Pos = GetWorldPos();

	Vector3 PlayerPos = Player->GetWorldPos();

	float Dir = PlayerPos.x - Pos.x;

	if (Dir > 1.f)
	{
		m_Flip = true;

		m_Stop = false;
	}

	else if (Dir < -1.f)
	{
		m_Flip = false;

		m_Stop = false;
	}

	else
	{
		m_Stop = true;
	}
}

void CMonsterManager::AIAttack(float DeltaTime)
{
	CPlayer2D* Player = (CPlayer2D*)m_Scene->GetPlayerObject();

	Vector3 Pos = GetWorldPos();

	Vector3 PlayerPos = Player->GetWorldPos();

	float Dir = PlayerPos.x - Pos.x;

	if (m_Attack)
	{
		if (Dir > 1.f)
		{
			m_Flip = true;
		}

		else if (Dir < -1.f)
		{
			m_Flip = false;
		}
	}
}

void CMonsterManager::AIDeath(float DeltaTime)
{
}

bool CMonsterManager::CheckDie()
{
	if (m_State == EMonster_State::Die)
	{
		return true;
	}

	return false;
}

void CMonsterManager::CollisionCallbackBegin(const CollisionResult& result)
{
	result.Src->GetCollisionProfile();

	if (!result.Dest->GetCollisionProfile())
	{
		return;
	}

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		m_Trace = true;

		m_State = EMonster_State::Trace;
	}
}

void CMonsterManager::AttackBegin(const CollisionResult& result)
{
	result.Src->GetCollisionProfile();

	if (!result.Dest->GetCollisionProfile())
	{
		return;
	}

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		m_State = EMonster_State::Attack;

		m_Hurt = true;

		m_Attack = true;
	}
}

void CMonsterManager::AnimationFinish()
{
	if (!m_Attack)
	{
		m_IsMove = rand() % 2;

		if (m_IsMove)
		{
			m_Flip = (bool)(rand() % 2);

			m_State = EMonster_State::Move;
		}

		else
		{
			m_State = EMonster_State::Idle;
		}

		return;
	}
}
