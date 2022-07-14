#include "SceneCollision.h"
#include "../Engine.h"
#include "CollisionSection.h"
#include "../Component/ColliderComponent.h"
#include "../Input.h"
#include "Viewport.h"
#include "Scene.h"

CSceneCollision::CSceneCollision() : m_Section(nullptr), m_MouseCollision(nullptr), m_WidgetClick(false)
{
}

CSceneCollision::~CSceneCollision()
{
	size_t Size = m_Section->vecSection.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_Section->vecSection[i]);
	}

	SAFE_DELETE(m_Section);
}

void CSceneCollision::Start()
{
	
}

bool CSceneCollision::Init()
{
	SetSectionSize(1000.f, 1000.f, 1.f);
	SetSectionCenter(0.f, 0.f, 0.f);
	SetSectionCount(10, 10, 1);
	CreateSection();

	return true;
}

bool CSceneCollision::CollisionWidget(float DeltaTime)
{
	// UI와 마우스와의 충돌처리를 한다.
	return m_WidgetClick = m_Scene->GetViewport()->CollisionMouse();
}

void CSceneCollision::Collision(float DeltaTime)
{
	// 마우스와 충돌을 하고 있던 물체가 제거가 된다면 마우스와 충돌한 충돌체 정보를 nullptr로 바꿔준다.
	auto iter = m_ColliderList.begin();
	auto iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			if (*iter == m_MouseCollision)
			{
				m_MouseCollision = nullptr;
			}

			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		++iter;
	}

	// 충돌체들을 각 자의 영역으로 포함시켜주도록 한다.
	CheckColliderSection();

	// 현재 충돌 영역이 겹치는지 판단한다.
	iter = m_ColliderList.begin();
	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetCurrentSectionCheck())
		{
			continue;
		}

		(*iter)->CurrentSectionCheck();

		// 이전 프레임에 충돌되었던 충돌체들이 같은 영역에 있는지를 판단한다.
		(*iter)->CheckPrevColliderSection();
	}

	// 먼저 마우스와 충돌체들을 체크한다.
	CollisionMouse(DeltaTime);

	// 충돌체끼리 체크한다.
	// 전체 Section을 반복하며 충돌을 진행한다.
	size_t	Size = m_Section->vecSection.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_Section->vecSection[i]->Collision(DeltaTime);
		m_Section->vecSection[i]->Clear();
	}

	iter = m_ColliderList.begin();
	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->ClearFrame();
	}
}

void CSceneCollision::CollisionMouse(float DeltaTime)
{
	bool MouseCollision = m_WidgetClick;

	// UI와 마우스와의 충돌처리를 한다.
	MouseCollision = m_Scene->GetViewport()->CollisionMouse();


	// UI와 마우스가 충돌된 물체가 없다면 월드공간의 물체와 충돌을 진행한다.
	if (!MouseCollision)
	{
		// 마우스가 충돌영역중 어느 충돌 영역에 존재하는지를 판단한다.
		// 단, 2D와 3D는 마우스 충돌 방식이 다르므로 2D, 3D를 구분하여 판단해야 한다.
		if (CEngine::GetInst()->GetEngineSpace() == Engine_Space::Space2D)
		{
			Vector2	MousePos = CInput::GetInst()->GetMouseWorld2DPos();

			MousePos.x -= m_Section->Min.x;
			MousePos.y -= m_Section->Min.y;

			int	IndexX = 0, IndexY = 0;

			IndexX = (int)(MousePos.x / m_Section->SectionSize.x);
			IndexY = (int)(MousePos.y / m_Section->SectionSize.y);

			IndexX = IndexX < 0 ? -1 : IndexX;
			IndexY = IndexY < 0 ? -1 : IndexY;

			IndexX = IndexX >= m_Section->CountX ? -1 : IndexX;
			IndexY = IndexY >= m_Section->CountY ? -1 : IndexY;

			if (IndexX != -1 && IndexY != -1)
			{
				CColliderComponent* ColliderMouse = m_Section->vecSection[IndexY * m_Section->CountX + IndexX]->CollisionMouse(true, DeltaTime);

				if (ColliderMouse)
				{
					MouseCollision = true;

					if (ColliderMouse != m_MouseCollision)
					{
						ColliderMouse->CallCollisionMouseCallback(Collision_State::Begin);
					}

					if (m_MouseCollision && m_MouseCollision != ColliderMouse)
					{
						m_MouseCollision->CallCollisionMouseCallback(Collision_State::End);
					}

					m_MouseCollision = ColliderMouse;
				}
			}
		}

		else
		{
		}
	}

	else
	{
		if (m_MouseCollision)
		{
			m_MouseCollision->CallCollisionMouseCallback(Collision_State::End);
			m_MouseCollision = nullptr;
		}
	}

	if (!MouseCollision)
	{
		if (m_MouseCollision)
		{
			m_MouseCollision->CallCollisionMouseCallback(Collision_State::End);
			m_MouseCollision = nullptr;
		}
	}
}

void CSceneCollision::SetSectionSize(const Vector3& Size)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->SectionSize = Size;
	m_Section->SectionTotalSize = m_Section->SectionSize * Vector3((float)m_Section->CountX, (float)m_Section->CountY, (float)m_Section->CountZ);
}

void CSceneCollision::SetSectionSize(float x, float y, float z)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->SectionSize = Vector3(x, y, z);
	m_Section->SectionTotalSize = m_Section->SectionSize * Vector3((float)m_Section->CountX, (float)m_Section->CountY, (float)m_Section->CountZ);
}

void CSceneCollision::SetSectionCenter(const Vector3& Center)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->Center = Center;
	m_Section->Min = m_Section->Center - m_Section->SectionTotalSize / 2.f;
	m_Section->Max = m_Section->Min + m_Section->SectionTotalSize;
}

void CSceneCollision::SetSectionCenter(float x, float y, float z)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->Center = Vector3(x, y, z);
	m_Section->Min = m_Section->Center - m_Section->SectionTotalSize / 2.f;
	m_Section->Max = m_Section->Min + m_Section->SectionTotalSize;
}

void CSceneCollision::SetSectionMin(const Vector3& Min)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->Min = Min;
	m_Section->SectionTotalSize = m_Section->Max - m_Section->Min;
	m_Section->SectionSize = m_Section->SectionTotalSize / Vector3((float)m_Section->CountX, (float)m_Section->CountY, (float)m_Section->CountZ);
	m_Section->Center = (m_Section->Min + m_Section->Max) / 2.f;
}

void CSceneCollision::SetSectionMin(float x, float y, float z)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->Min = Vector3(x, y, z);
	m_Section->SectionTotalSize = m_Section->Max - m_Section->Min;
	m_Section->SectionSize = m_Section->SectionTotalSize / Vector3((float)m_Section->CountX, (float)m_Section->CountY, (float)m_Section->CountZ);
	m_Section->Center = (m_Section->Min + m_Section->Max) / 2.f;
}

void CSceneCollision::SetSectionMax(const Vector3& Max)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->Max = Max;
	m_Section->SectionTotalSize = m_Section->Max - m_Section->Min;
	m_Section->SectionSize = m_Section->SectionTotalSize / Vector3((float)m_Section->CountX, (float)m_Section->CountY, (float)m_Section->CountZ);
	m_Section->Center = (m_Section->Min + m_Section->Max) / 2.f;
}

void CSceneCollision::SetSectionMax(float x, float y, float z)
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	m_Section->Max = Vector3(x, y, z);
	m_Section->SectionTotalSize = m_Section->Max - m_Section->Min;
	m_Section->SectionSize = m_Section->SectionTotalSize / Vector3((float)m_Section->CountX, (float)m_Section->CountY, (float)m_Section->CountZ);
	m_Section->Center = (m_Section->Min + m_Section->Max) / 2.f;
}

void CSceneCollision::SetSectionCount(int CountX, int CountY, int CountZ)
{
	m_Section->CountX = CountX;
	m_Section->CountY = CountY;
	m_Section->CountZ = CountZ;

	m_Section->SectionTotalSize = m_Section->SectionSize * Vector3((float)CountX, (float)CountY, (float)CountZ);
	m_Section->Min = m_Section->Center - m_Section->SectionTotalSize / 2.f;
	m_Section->Max = m_Section->Min + m_Section->SectionTotalSize;
}

void CSceneCollision::CreateSection()
{
	if (!m_Section)
	{
		m_Section = new CollisionSectionInfo;
	}

	for (int z = 0; z < m_Section->CountZ; z++)
	{
		for (int y = 0; y < m_Section->CountY; y++)
		{
			for (int x = 0; x < m_Section->CountX; x++)
			{
				CCollisionSection* Section = new CCollisionSection;

				Section->Init(x, y, z, z * (m_Section->CountX * m_Section->CountY) + y * m_Section->CountX + x, 
					m_Section->Min, m_Section->Max, m_Section->SectionSize, m_Section->SectionTotalSize);

				m_Section->vecSection.push_back(Section);
			}
		}
	}
}

void CSceneCollision::Clear()
{
	size_t	Size = m_Section->vecSection.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_Section->vecSection[i]);
	}

	SAFE_DELETE(m_Section);
}

void CSceneCollision::AddCollider(CColliderComponent* Collider)
{
	m_ColliderList.push_back(Collider);
}

void CSceneCollision::CheckColliderSection()
{
	auto iter = m_ColliderList.begin();
	auto iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; iter++)
	{
		CColliderComponent* Collider = *iter;
		
		Vector3	Min = Collider->GetMin();
		Vector3	Max = Collider->GetMax();

		Min -= m_Section->Min;
		Max -= m_Section->Min;

		int	IndexMinX, IndexMinY, IndexMinZ;
		int	IndexMaxX, IndexMaxY, IndexMaxZ;

		IndexMinX = (int)(Min.x / m_Section->SectionSize.x);
		IndexMinY = (int)(Min.y / m_Section->SectionSize.y);
		IndexMinZ = (int)(Min.z / m_Section->SectionSize.z);

		IndexMaxX = (int)(Max.x / m_Section->SectionSize.x);
		IndexMaxY = (int)(Max.y / m_Section->SectionSize.y);
		IndexMaxZ = (int)(Max.z / m_Section->SectionSize.z);

		IndexMinX = IndexMinX < 0 ? 0 : IndexMinX;
		IndexMinY = IndexMinY < 0 ? 0 : IndexMinY;
		IndexMinZ = IndexMinZ < 0 ? 0 : IndexMinZ;

		IndexMaxX = IndexMaxX >= m_Section->CountX ? m_Section->CountX - 1 : IndexMaxX;
		IndexMaxY = IndexMaxY >= m_Section->CountY ? m_Section->CountY - 1 : IndexMaxY;
		IndexMaxZ = IndexMaxZ >= m_Section->CountZ ? m_Section->CountZ - 1 : IndexMaxZ;

		for (int z = IndexMinZ; z <= IndexMaxZ; ++z)
		{
			for (int y = IndexMinY; y <= IndexMaxY; ++y)
			{
				for (int x = IndexMinX; x <= IndexMaxX; ++x)
				{
					int	Index = z * (m_Section->CountX * m_Section->CountY) + y * m_Section->CountX + x;

					m_Section->vecSection[Index]->AddCollider(Collider);
				}
			}
		}
	}
}
