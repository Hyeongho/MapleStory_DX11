#pragma once

#include "NPCManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderPixel.h"
#include "Component/ColliderBox2D.h"

class CSeolHui :
    public CNPCManager
{
public:
	CSeolHui();
	CSeolHui(const CSeolHui& obj);
	virtual ~CSeolHui();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderPixel> m_Body;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSeolHui* Clone();

private:
	void CollisionCallbackBegin(const CollisionResult& result);
	void CollisionCallbackEnd(const CollisionResult& result);
};

