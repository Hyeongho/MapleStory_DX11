#include "ColliderComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneCollision.h"
#include "../Collision/CollisionManager.h"
#include "../Resource/Shader/ColliderConstantBuffer.h"

CColliderComponent::CColliderComponent()
{
	SetTypeID<CColliderComponent>();
	m_ComponentType = Component_Type::SceneComponent;
	m_Render = true;

	m_CurrentSectionCheck = false;
	m_Profile = nullptr;
	m_MouseCollision = false;
	m_CBuffer = nullptr;

	SetLayerName("Collider");
}

CColliderComponent::CColliderComponent(const CColliderComponent& com) : CSceneComponent(com)
{
	m_MouseCollision = false;
	m_CurrentSectionCheck = false;
	m_Render = com.m_Render;
	m_Profile = com.m_Profile;
	m_CBuffer = com.m_CBuffer->Clone();
	m_Mesh = com.m_Mesh;
	m_Shader = com.m_Shader;
}

CColliderComponent::~CColliderComponent()
{
	SAFE_DELETE(m_CBuffer);

	auto iter = m_PrevCollisionList.begin();
	auto iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->DeletePrevCollision(this);
		(*iter)->CallCollisionCallback(Collision_State::End);
		CallCollisionCallback(Collision_State::End);
	}
}

void CColliderComponent::SetCollisionProfile(const std::string& Name)
{
	m_Profile = CCollisionManager::GetInst()->FindProfile(Name);
}

void CColliderComponent::CheckPrevColliderSection()
{
	auto iter = m_PrevCollisionList.begin();
	auto iterEnd = m_PrevCollisionList.end();

	// ���������ӿ� �浹�Ǿ��� �浹ü���� �ݺ��ϸ� ������ ��ġ������ �Ǵ��Ѵ�.
	// ���� ���������ӿ� �浹�� �Ǿ��µ� ���� ���� �ٸ� ������ �����Ѵٸ� �ش� �浹ü�ʹ� �浹 ���ɼ���
	// �����Ƿ� �浹�Ǿ��ٰ� �������°����� �Ǵ����ָ� �ȴ�.
	for (; iter != iterEnd;)
	{
		bool Check = false;

		// �浹������ üũ�Ѵ�.
		size_t	Size = m_vecSectionIndex.size();

		for (size_t i = 0; i < Size; i++)
		{
			size_t	DestSize = (*iter)->m_vecSectionIndex.size();

			for (size_t j = 0; j < DestSize; j++)
			{
				if (m_vecSectionIndex[i] == (*iter)->m_vecSectionIndex[j])
				{
					Check = true;
					break;
				}
			}

			if (Check)
			{
				break;
			}
		}

		// ���� ��ġ�� �浹������ �����Ƿ� �پ��ִٰ� �������� ���̴�.
		if (!Check)
		{
			CallCollisionCallback(Collision_State::End);
			(*iter)->CallCollisionCallback(Collision_State::End);

			// ���� ���� �浹��Ͽ��� �������ش�.
			(*iter)->DeletePrevCollision(this);
					
			iter = m_PrevCollisionList.erase(iter);
			iterEnd = m_PrevCollisionList.end();
			continue;
		}

		iter++;
	}
}

void CColliderComponent::SendPrevCollisionEnd()
{
	if (m_PrevCollisionList.empty())
	{
		return;
	}

	auto iter = m_PrevCollisionList.begin();
	auto iterEnd = m_PrevCollisionList.end();

	for ( ; iter != iterEnd; iter++)
	{
		(*iter)->DeletePrevCollision(this);

		(*iter)->m_Result.Src = *iter;
		(*iter)->m_Result.Dest = this;
		(*iter)->CallCollisionCallback(Collision_State::End);

		m_Result.Src = this;
		m_Result.Dest = *iter;
		CallCollisionCallback(Collision_State::End);
	}

	m_PrevCollisionList.clear();
}

void CColliderComponent::AddPrevCollision(CColliderComponent* Collider)
{
	m_PrevCollisionList.push_back(Collider);
}

void CColliderComponent::DeletePrevCollision(CColliderComponent* Collider)
{
	auto iter = m_PrevCollisionList.begin();
	auto iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == Collider)
		{
			m_PrevCollisionList.erase(iter);
			return;
		}
	}
}

bool CColliderComponent::EmptyPrevCollision()
{
	return m_PrevCollisionList.empty();
}

bool CColliderComponent::CheckPrevCollision(CColliderComponent* Collider)
{
	auto iter = m_PrevCollisionList.begin();
	auto iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == Collider)
		{
			return true;
		}
	}

	return false;
}

bool CColliderComponent::CheckCurrentFrameCollision(CColliderComponent* Collider)
{
	auto iter = m_CurrentCollisionList.begin();
	auto iterEnd = m_CurrentCollisionList.end();

	for (; iter != iterEnd; iter++)
	{
		if (*iter == Collider)
		{
			return true;
		}
	}

	return false;
}

void CColliderComponent::AddCurrentFrameCollision(CColliderComponent* Collider)
{
	if (!CheckCurrentFrameCollision(Collider))
	{
		m_CurrentCollisionList.push_back(Collider);
	}
}

void CColliderComponent::CallCollisionCallback(Collision_State State)
{
	auto iter = m_CollisionCallback[(int)State].begin();
	auto iterEnd = m_CollisionCallback[(int)State].end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)(m_Result);
	}
}

void CColliderComponent::CallCollisionMouseCallback(Collision_State State)
{
	if (State == Collision_State::End)
	{
		m_MouseCollision = false;
	}

	auto iter = m_CollisionMouseCallback[(int)State].begin();
	auto iterEnd = m_CollisionMouseCallback[(int)State].end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)(m_MouseResult);
	}
}

void CColliderComponent::ClearFrame()
{
	m_vecSectionIndex.clear();
	m_CurrentCollisionList.clear();
	m_CurrentSectionCheck = false;
}

void CColliderComponent::Start()
{
	CSceneComponent::Start();

	m_Scene->GetCollision()->AddCollider(this);
}

bool CColliderComponent::Init()
{
	if (!CSceneComponent::Init())
	{
		return false;
	}

	SetCollisionProfile("Object");

	m_CBuffer = new CColliderConstantBuffer;

	m_CBuffer->Init();

	m_CBuffer->SetColliderColor(Vector4(0.f, 1.f, 0.f, 1.f));

	m_Shader = CResourceManager::GetInst()->FindShader("ColliderShader");

	return true;
}

void CColliderComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CColliderComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CColliderComponent::CheckCollision()
{
	CSceneComponent::CheckCollision();
}

void CColliderComponent::PrevRender()
{
#ifdef _DEBUG

	CSceneComponent::PrevRender();

#endif // _DEBUG
}

void CColliderComponent::Render()
{
#ifdef _DEBUG

	CSceneComponent::Render();

#endif // _DEBUG
}

void CColliderComponent::PostRender()
{
#ifdef _DEBUG

	CSceneComponent::PostRender();

#endif // _DEBUG
}

CColliderComponent* CColliderComponent::Clone()
{
	return nullptr;
}

void CColliderComponent::Save(FILE* File)
{
	CSceneComponent::Save(File);

	fwrite(&m_ColliderType, sizeof(Collider_Type), 1, File);
	fwrite(&m_Offset, sizeof(Vector3), 1, File);
	fwrite(&m_Min, sizeof(Vector3), 1, File);
	fwrite(&m_Max, sizeof(Vector3), 1, File);
}

void CColliderComponent::Load(FILE* File)
{
	CSceneComponent::Load(File);

	fread(&m_ColliderType, sizeof(Collider_Type), 1, File);
	fread(&m_Offset, sizeof(Vector3), 1, File);
	fread(&m_Min, sizeof(Vector3), 1, File);
	fread(&m_Max, sizeof(Vector3), 1, File);
}
