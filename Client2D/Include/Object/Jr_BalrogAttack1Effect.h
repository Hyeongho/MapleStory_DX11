#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CJr_BalrogAttack1Effect :
    public CGameObject
{
    friend class CScene;

protected:
    CJr_BalrogAttack1Effect();
    CJr_BalrogAttack1Effect(const CJr_BalrogAttack1Effect& obj);
    virtual ~CJr_BalrogAttack1Effect();

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
    virtual CJr_BalrogAttack1Effect* Clone();

public:
    void SetEnable(class CJr_Balrog* Balrog);

    void OnCollisionBegin(const CollisionResult& result);
    void AnimationFinish();
};

