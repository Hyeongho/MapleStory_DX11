#include "GameObject.h"
#include "../Scene/SceneManager.h"
#include "../Component/TileMapComponent.h"
#include "../PathManager.h"
#include "../Component/NavAgent.h"

CGameObject::CGameObject() : m_Scene(nullptr), m_Parent(nullptr)
{
	SetTypeID<CGameObject>();

	m_PrevPos.y = -1.0f;
}

CGameObject::CGameObject(const CGameObject& obj)
{
	*this = obj;

	m_PrevPos.y = -1.f;

	m_RefCount = 0;

	if (obj.m_RootComponent)
	{
		m_RootComponent = obj.m_RootComponent->Clone();

		m_RootComponent->SetGameObject(this);

		m_RootComponent->SetSceneComponent(this);
	}

	m_vecObjectComponent.clear();

	size_t	Size = obj.m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent.push_back(obj.m_vecObjectComponent[i]->Clone());

		m_vecObjectComponent[i]->SetGameObject(this);
	}

	m_PrevPos = obj.m_PrevPos;
}

CGameObject::~CGameObject()
{
}

void CGameObject::SetScene(CScene* Scene)
{
	m_Scene = Scene;
}

void CGameObject::Destroy()
{
	CRef::Destroy();

	m_RootComponent->Destroy();

	size_t Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_vecObjectComponent[i]->Destroy();
	}
}

CComponent* CGameObject::FindComponent(const std::string& Name)
{
	{
		auto iter = m_SceneComponentList.begin();
		auto iterEnd = m_SceneComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
			{
				return *iter;
			}
		}
	}

	{
		auto iter = m_vecObjectComponent.begin();
		auto iterEnd = m_vecObjectComponent.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
			{
				return *iter;
			}
		}
	}

	return nullptr;
}

void CGameObject::GetAllSceneComponentsName(std::vector<FindComponentName>& vecNames)
{
	if (!m_RootComponent)
	{
		return;
	}

	m_RootComponent->GetAllSceneComponentsName(vecNames);
}

void CGameObject::Start()
{
	if (m_RootComponent)
	{
		m_RootComponent->Start();
	}

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Start();
	}
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
	if (!IsEnable())
	{
		return;
	}

	size_t Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Update(DeltaTime);
	}

	if (m_RootComponent)
	{
		m_RootComponent->Update(DeltaTime);
	}
}

void CGameObject::PostUpdate(float DeltaTime)
{
	if (!IsEnable())
	{
		return;
	}

	size_t Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PostUpdate(DeltaTime);
	}

	if (m_RootComponent)
	{
		m_RootComponent->PostUpdate(DeltaTime);
	}
}

void CGameObject::AddCollision()
{
	if (m_RootComponent)
	{
		m_RootComponent->CheckCollision();
	}
}

void CGameObject::PrevRender()
{
	if (!IsEnable())
	{
		return;
	}

	size_t Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PrevRender();
	}

	if (m_RootComponent)
	{
		m_RootComponent->PrevRender();
	}
}

void CGameObject::Render()
{
	if (!IsEnable())
	{
		return;
	}

	size_t Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Render();
	}

	if (m_RootComponent)
	{
		m_RootComponent->Render();
	}
}

void CGameObject::PostRender()
{
	if (!IsEnable())
	{
		return;
	}

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PostRender();
	}

	if (m_RootComponent)
	{
		m_RootComponent->PostRender();
	}

	Vector3 Pos = GetWorldPos();

	m_PrevPos = Pos;
	//m_Velocity = Vector2(0.f, 0.f);
}

CGameObject* CGameObject::Clone()
{
	return new CGameObject(*this);
}

//float CGameObject::SetDamage(float Damage)
//{
//	return Damage;
//}

void CGameObject::Save(FILE* File)
{
	CRef::Save(File);

	if (m_RootComponent)
	{
		bool Root = true;
		fwrite(&Root, sizeof(bool), 1, File);

		size_t TypeID = m_RootComponent->GetTypeID();
		fwrite(&TypeID, sizeof(size_t), 1, File);

		m_RootComponent->Save(File);
	}

	else
	{
		bool Root = false;
		fwrite(&Root, sizeof(bool), 1, File);
	}

	int	ObjComponentCount = (int)m_vecObjectComponent.size();

	fwrite(&ObjComponentCount, sizeof(int), 1, File);

	for (int i = 0; i < ObjComponentCount; i++)
	{
		size_t TypeID = m_vecObjectComponent[i]->GetTypeID();
		fwrite(&TypeID, sizeof(size_t), 1, File);

		m_vecObjectComponent[i]->Save(File);
	}
}

void CGameObject::Load(FILE* File)
{
	CRef::Load(File);

	bool Root = false;
	fread(&Root, sizeof(bool), 1, File);

	if (Root)
	{
		size_t TypeID = 0;
		fread(&TypeID, sizeof(size_t), 1, File);

		CSceneManager::GetInst()->CallCreateComponent(this, TypeID);

		m_RootComponent->Load(File);
	}

	int	ObjComponentCount = 0;

	fread(&ObjComponentCount, sizeof(int), 1, File);

	for (int i = 0; i < ObjComponentCount; i++)
	{
		size_t TypeID = 0;
		fread(&TypeID, sizeof(size_t), 1, File);

		CComponent* Component = CSceneManager::GetInst()->CallCreateComponent(this, TypeID);

		Component->Load(File);

		m_vecObjectComponent.push_back((CObjectComponent*)Component);
	}
}

void CGameObject::Save(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");

	if (!File)
	{
		return;
	}

	Save(File);

	fclose(File);
}

void CGameObject::Load(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
	{
		return;
	}

	Load(File);

	fclose(File);
}

void CGameObject::Save(const char* FileName, const std::string& PathName)
{
	char FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
	{
		strcpy_s(FullPath, Info->PathMultibyte);
	}

	strcat_s(FullPath, FileName);

	Save(FullPath);
}

void CGameObject::Load(const char* FileName, const std::string& PathName)
{
	char FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
	{
		strcpy_s(FullPath, Info->PathMultibyte);
	}

	strcat_s(FullPath, FileName);

	Load(FullPath);
}

void CGameObject::Move(const Vector3& EndPos)
{
	size_t Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; i++)
	{
		if (m_vecObjectComponent[i]->CheckType<CNavAgent>())
		{
			((CNavAgent*)m_vecObjectComponent[i].Get())->Move(EndPos);
			break;
		}
	}
}