#pragma once

#include "SkillManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "MonsterManager.h"

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

    CAnimationSequence2DInstance* m_Anim;

    std::vector<CMonsterManager*> m_Monster;

    Vector3 m_TargetPos;
    Vector2 m_TargetSize;

    std::thread t1;
    std::mutex m1;

public:
    void SetCollisionProfile(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBladeFury* Clone();
    virtual void SetEnable();

public:
    void OnCollisionBegin(const CollisionResult& result);
    void AnimationFinish();

    void Attack();

private:
    void PrintDamage();
};

