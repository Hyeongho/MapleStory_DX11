#include "SkillManager.h"

CSkillManager::CSkillManager() : m_obj(nullptr)
{
}

CSkillManager::CSkillManager(const CSkillManager& obj) : CGameObject(obj)
{
}

CSkillManager::~CSkillManager()
{
}

void CSkillManager::Start()
{
	CGameObject::Start();
}

bool CSkillManager::Init()
{
	CGameObject::Init();

	return true;
}

void CSkillManager::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSkillManager::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSkillManager* CSkillManager::Clone()
{
	return new CSkillManager(*this);;
}

void CSkillManager::SetEnable(bool Enable)
{
}
