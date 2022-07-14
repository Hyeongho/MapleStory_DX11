#pragma once

#include "SceneComponent.h"

class CColliderComponent :
    public CSceneComponent
{
    friend class CGameObject;
    friend class CCollision;

protected:
    CColliderComponent();
    CColliderComponent(const CColliderComponent& com);
    virtual ~CColliderComponent();

protected:
    Collider_Type m_ColliderType;
    Vector3 m_Offset;
    Vector3 m_Min;
    Vector3 m_Max;
    std::vector<int> m_vecSectionIndex;
    std::list<CColliderComponent*> m_PrevCollisionList;
    std::list<CColliderComponent*> m_CurrentCollisionList; // 현재 프레임에 이전 영역에서 충돌된 목록
    CollisionProfile* m_Profile;
    bool m_CurrentSectionCheck;
    CollisionResult m_Result;
    CollisionResult m_MouseResult;
    std::list<std::function<void(const CollisionResult&)>> m_CollisionCallback[(int)Collision_State::Max];
    std::list<std::function<void(const CollisionResult&)>> m_CollisionMouseCallback[(int)Collision_State::Max];
    bool m_MouseCollision;
    CSharedPtr<class CMesh> m_Mesh;
    CSharedPtr<class CShader> m_Shader;
    class CColliderConstantBuffer* m_CBuffer;

public:
    Collider_Type GetColliderType() const
    {
        return m_ColliderType;
    }

    void SetOffset(const Vector3& Offset)
    {
        m_Offset = Offset;
    }

    void SetOffset(float x, float y, float z)
    {
        m_Offset = Vector3(x, y, z);
    }

    Vector3 GetOffset() const
    {
        return m_Offset;
    }

    Vector3 GetMin() const
    {
        return m_Min;
    }

    Vector3 GetMax() const
    {
        return m_Max;
    }

    CollisionResult GetCollisionResult()    const
    {
        return m_Result;
    }

    CollisionProfile* GetCollisionProfile() const
    {
        return m_Profile;
    }

    void AddSectionIndex(int Index)
    {
        m_vecSectionIndex.push_back(Index);
    }

    void CurrentSectionCheck()
    {
        m_CurrentSectionCheck = true;
    }

    bool GetCurrentSectionCheck() const
    {
        return m_CurrentSectionCheck;
    }

    void SetCollisionProfile(const std::string& Name);
    void CheckPrevColliderSection();
    void AddPrevCollision(CColliderComponent* Collider);
    void DeletePrevCollision(CColliderComponent* Collider);
    bool EmptyPrevCollision();
    bool CheckPrevCollision(CColliderComponent* Collider);
    bool CheckCurrentFrameCollision(CColliderComponent* Collider);
    void AddCurrentFrameCollision(CColliderComponent* Collider);
    void CallCollisionCallback(Collision_State State);
    void CallCollisionMouseCallback(Collision_State State);
    void ClearFrame();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void CheckCollision();
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CColliderComponent* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
    virtual bool Collision(CColliderComponent* Dest) = 0;
    virtual bool CollisionMouse(const Vector2& MousePos) = 0;

public:
    template <typename T>
    void AddCollisionCallback(Collision_State State, T* Obj, void(T::* Func)(const CollisionResult&))
    {
        m_CollisionCallback[(int)State].push_back(std::bind(Func, Obj, std::placeholders::_1));
    }

    template <typename T>
    void AddCollisionMouseCallback(Collision_State State, T* Obj, void(T::* Func)(const CollisionResult&))
    {
        m_CollisionMouseCallback[(int)State].push_back(std::bind(Func, Obj, std::placeholders::_1));
    }
};

