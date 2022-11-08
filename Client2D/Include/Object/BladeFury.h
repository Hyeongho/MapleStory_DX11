#pragma once

#include "SkillManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CBladeFury :
    public CSkillManager
{
    friend class CScene;

protected:
    CBladeFury();
    CBladeFury(const CBladeFury& obj);
    virtual ~CBladeFury();

private:
    CSharedPtr<CSceneComponent> m_Muzzle;
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderBox2D> m_Body;

    Vector3 m_TargetPos;
    Vector2 m_TargetSize;

public:
    void SetCollisionProfile(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBladeFury* Clone();

public:
    void OnCollisionBegin(const CollisionResult& result);
    void AnimationFinish();
};

