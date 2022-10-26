#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CJr_Balrog :
    public CMonsterManager
{
public:
	CJr_Balrog();
	CJr_Balrog(const CJr_Balrog& obj);
	virtual ~CJr_Balrog();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CJr_Balrog* Clone();
};

