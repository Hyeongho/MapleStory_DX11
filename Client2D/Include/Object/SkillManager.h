#pragma once

#include "GameObject/GameObject.h"
#include "MonsterManager.h"

class CSkillManager :
    public CGameObject
{
public:
	CSkillManager();
	CSkillManager(const CSkillManager& obj);
	virtual ~CSkillManager();

protected:
	int m_Damage;
	CMonsterManager* m_obj;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkillManager* Clone();
	virtual void SetEnable(bool Enable);
};

