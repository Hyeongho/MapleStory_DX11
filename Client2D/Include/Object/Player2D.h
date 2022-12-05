#pragma once

#include "ObjectManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"
#include "Component/RigidBody.h"
#include "Component/Gravity.h"
#include "../Widget/PlayerStatus.h"
#include "Data/Data.h"
#include "../ClientInfo.h"
#include "PhantomBlow.h"
#include "BladeFury.h"

class CPlayer2D :
    public CObjectManager
{
    friend class CScene;
    friend class CPlayerAnimation2D;
    friend class CPlayerManager;

protected:
    CPlayer2D();
    CPlayer2D(const CPlayer2D& obj);
    virtual ~CPlayer2D();

private:
    std::thread t1; // 스킬 이펙트 스레드
    std::mutex m1;

    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CRigidBody> m_RigidBody;
    CSharedPtr<CGravity> m_Gravity;
    CSharedPtr<CColliderBox2D> m_Body;
    CSharedPtr<CColliderBox2D> m_Bottom;
    CSharedPtr<CCameraComponent> m_Camera;
    CSharedPtr<CSceneComponent> m_Muzzle;
    CSharedPtr<CPhantomBlow> m_PhantomBlow;
    CSharedPtr<CBladeFury> m_BladeFury;

    CPlayerStatus* m_PlayerStatus;

    //CSharedPtr<CData> m_Data;

    //CharacterInfo m_CharacterInfo;

    EPlayer_State m_State;

    bool m_SolW;
    float m_WDistance;
    float m_Opacity;
    bool m_Flip;
    bool m_Hurt;

    float m_HurtTime;

public:
    bool m_IsMove;
    static Gender m_Gender;

public:
    EPlayer_State GetPlayerState() const
    {
        return m_State;
    }

    bool GetFlip() const
    {
        return m_Flip;
    }

    void SetGround(bool Ground)
    {
        m_Gravity->SetGround(Ground);
    }

    void SetHurt(bool Hurt)
    {
        m_Hurt = Hurt;
    }

    bool GetHurt() const
    {
        return m_Hurt;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CPlayer2D* Clone();

private:
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void MoveUp(float DeltaTime);
    void Stop(float DeltaTime);
    void Jump(float DeltaTime);
    void SwingD1(float DeltaTime);
    void SwingD2(float DeltaTime);
    void StabD1(float DeltaTime);
    void PhantomBlow(float DeltaTime);
    void BladeFury(float DeltaTime);

    void OnHit(float DeltaTime);

    void PlayPhantomBlow();
    void PlayBladeFury();

private:
    void CollisionCallback(const CollisionResult& result);
    void CollisionExit(const CollisionResult& result);

private:
    void AnimationFinish();
};

