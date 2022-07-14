#pragma once

#include "MonsterManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CTestMonster :
    public CMonsterManager
{
public:
	CTestMonster();
	CTestMonster(const CTestMonster& obj);
	virtual ~CTestMonster();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;
	CSharedPtr<CColliderBox2D> m_Sensor;

	bool m_SolW;
	float m_WDistance;
	float m_Opacity;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTestMonster* Clone();

private:
	void CollisionCallback(const CollisionResult& result);
};

