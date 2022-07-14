#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../ClientInfo.h"

class CPotal :
    public CGameObject
{
    friend class CScene;

protected:
    CPotal();
    CPotal(const CPotal& obj);
    virtual ~CPotal();

private:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderBox2D> m_Body;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CPotal* Clone();

private:
    void CollisionCallbackBegin(const CollisionResult& result);
    void CollisionCallbackEnd(const CollisionResult& result);
};

