#include "NavAgent.h"
#include "../Scene/Scene.h"
#include "../Scene/NavigationManager.h"
#include "SceneComponent.h"
#include "../GameObject/GameObject.h"

CNavAgent::CNavAgent() : m_MoveSpeed(300.f)
{
	SetTypeID<CNavAgent>();
}

CNavAgent::CNavAgent(const CNavAgent& com) : CObjectComponent(com)
{
	m_MoveSpeed = com.m_MoveSpeed;
}

CNavAgent::~CNavAgent()
{
}

void CNavAgent::SetUpdateComponent(CSceneComponent* UpdateComponent)
{
	m_UpdateComponent = UpdateComponent;
}

bool CNavAgent::Move(const Vector3& EndPos)
{
	if (!m_UpdateComponent)
	{
		return false;
	}

	return m_Scene->GetNavigationManager()->FindPath<CNavAgent, CSceneComponent>(this, &CNavAgent::PathResult, m_UpdateComponent, EndPos);
}

void CNavAgent::Start()
{
	if (!m_UpdateComponent)
	{
		m_UpdateComponent = m_Object->GetRootComponent();
	}
}

bool CNavAgent::Init()
{
	return true;
}

void CNavAgent::Update(float DeltaTime)
{
	if (m_UpdateComponent)
	{
		if (!m_PathList.empty())
		{
			Vector3	TargetPos = m_PathList.front();
			Vector3	Pos = m_UpdateComponent->GetWorldPos();

			float TargetDistance = Pos.Distance(TargetPos);

			Vector3	Dir = TargetPos - Pos;
			Dir.Normalize();

			float Dist = m_MoveSpeed * DeltaTime;

			if (TargetDistance <= Dist)
			{
				m_PathList.pop_front();
				Dist = TargetDistance;
			}

			m_UpdateComponent->AddWorldPos(Dir * Dist);
		}
	}
}

void CNavAgent::PostUpdate(float DeltaTime)
{
}

void CNavAgent::PrevRender()
{
}

void CNavAgent::Render()
{
}

void CNavAgent::PostRender()
{
}

CNavAgent* CNavAgent::Clone()
{
	return new CNavAgent(*this);
}

void CNavAgent::PathResult(const std::list<Vector3>& PathList)
{
	m_PathList.clear();
	m_PathList = PathList;
}
