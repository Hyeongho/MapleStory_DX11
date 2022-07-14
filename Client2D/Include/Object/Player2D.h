#pragma once

#include "ObjectManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"
#include "../Widget/PlayerStatus.h"
#include "Data/Data.h"
#include "../ClientInfo.h"

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
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderBox2D> m_Body;
    CSharedPtr<CColliderBox2D> m_Bottom;
    CSharedPtr<CCameraComponent> m_Camera;
    CSharedPtr<CSceneComponent> m_Muzzle;

    CPlayerStatus* m_PlayerStatus;

    //CSharedPtr<CData> m_Data;

    //CharacterInfo m_CharacterInfo;

    EPlayer_State m_State;

    bool m_SolW;
    float m_WDistance;
    float m_Opacity;
    bool m_Flip;

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

private:
    void CollisionCallback(const CollisionResult& result);

private:
    void AnimationFinish();
};

