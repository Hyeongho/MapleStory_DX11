#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CBodyAttack3AreaWarning :
    public CGameObject
{
    friend class CScene;

protected:
    CBodyAttack3AreaWarning();
    CBodyAttack3AreaWarning(const CBodyAttack3AreaWarning& obj);
    virtual ~CBodyAttack3AreaWarning();

private:
    CSharedPtr<CSceneComponent> m_Muzzle;
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderBox2D> m_Body;

    CAnimationSequence2DInstance* m_Anim;

    Vector3 m_TargetPos;
    Vector2 m_TargetSize;

public:
    void SetCollisionProfile(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBodyAttack3AreaWarning* Clone();

public:
    void SetEnable();

    void OnCollisionBegin(const CollisionResult& result);
    void AnimationFinish();
};

