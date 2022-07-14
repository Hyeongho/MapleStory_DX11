#include "Component.h"

CComponent::CComponent() : m_Scene(nullptr), m_Object(nullptr)
{
}

CComponent::CComponent(const CComponent& com)
{
	*this = com;
	m_RefCount = 0;

	m_Object = nullptr;
}

CComponent::~CComponent()
{
}

void CComponent::SetScene(CScene* Scene)
{
	m_Scene = Scene;
}

void CComponent::SetGameObject(CGameObject* Object)
{
	m_Object = Object;
}

void CComponent::Destroy()
{
	CRef::Destroy();
}

void CComponent::Start()
{
}

bool CComponent::Init()
{
	return true;
}

void CComponent::Save(FILE* File)
{
	CRef::Save(File);

	fwrite(&m_ComponentType, sizeof(Component_Type), 1, File);
}

void CComponent::Load(FILE* File)
{
	CRef::Load(File);

	fread(&m_ComponentType, sizeof(Component_Type), 1, File);
}
