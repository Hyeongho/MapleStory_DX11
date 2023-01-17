#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CBodyAttack2Effect :
    public CGameObject
{
    friend class CScene;

protected:
    CBodyAttack2Effect();
    CBodyAttack2Effect(const CBodyAttack2Effect& obj);
    virtual ~CBodyAttack2Effect();

private:
    CSharedPtr<CSceneComponent> m_Muzzle;
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderBox2D> m_Body;

    Vector3 m_TargetPos;
    Vector2 m_TargetSize;

public:
    void SetCollisionProfile(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBodyAttack2Effect* Clone();

public:
    void OnCollisionBegin(const CollisionResult& result);

    void Attack();

    void AnimationFinish();
};
