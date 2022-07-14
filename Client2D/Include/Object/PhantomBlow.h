#pragma once

#include "SkillManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/EffectComponent.h"

class CPhantomBlow :
    public CSkillManager
{
    friend class CScene;

protected:
    CPhantomBlow();
    CPhantomBlow(const CPhantomBlow& obj);
    virtual ~CPhantomBlow();

private:
    CSharedPtr<CSceneComponent> m_Muzzle;
    CSharedPtr<CSpriteComponent> m_Sprite1;
    CSharedPtr<CSpriteComponent> m_Sprite2;
    CSharedPtr<CColliderBox2D> m_Body;

    Vector3 m_TargetPos;
    Vector2 m_TargetSize;

    CAnimationSequence2DInstance* m_Anim1;
    CAnimationSequence2DInstance* m_Anim2;

public:
    void SetCollisionProfile(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CPhantomBlow* Clone();

private:
    void OnCollisionBegin(const CollisionResult& result);
    void AnimationFinish();

public:
    void Attack();
};

