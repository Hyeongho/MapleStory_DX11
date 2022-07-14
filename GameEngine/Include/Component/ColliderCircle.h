#pragma once

#include "ColliderComponent.h"

class CColliderCircle :
    public CColliderComponent
{
    friend class CGameObject;

protected:
    CColliderCircle();
    CColliderCircle(const CColliderCircle& com);
    virtual ~CColliderCircle();

protected:
    CircleInfo m_Info;

public:
    CircleInfo GetInfo() const
    {
        return m_Info;
    }

    void SetInfo(const Vector2& Center, float Radius)
    {
        m_Info.Center = Center;
        m_Info.Radius = Radius;

        SetWorldScale(m_Info.Radius * 2.f, m_Info.Radius * 2.f, 1.f);
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CColliderCircle* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
    virtual bool Collision(CColliderComponent* Dest);
    virtual bool CollisionMouse(const Vector2& MousePos);
};

