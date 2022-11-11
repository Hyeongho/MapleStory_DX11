#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CRightAttack1AreaWarning :
    public CGameObject
{
    friend class CScene;

protected:
    CRightAttack1AreaWarning();
    CRightAttack1AreaWarning(const CRightAttack1AreaWarning& obj);
    virtual ~CRightAttack1AreaWarning();

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
    virtual CRightAttack1AreaWarning* Clone();

public:
    void OnCollisionBegin(const CollisionResult& result);
    void AnimationFinish();
};

