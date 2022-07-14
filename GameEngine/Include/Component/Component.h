#pragma once

#include "../Ref.h"

class CComponent :
    public CRef
{
    friend class CGameObject;

protected:
    CComponent();
    CComponent(const CComponent& com);
    virtual ~CComponent() = 0;

protected:
    class CScene* m_Scene;
    class CGameObject* m_Object;

public:
    virtual void SetScene(class CScene* Scene);
    virtual void SetGameObject(class CGameObject* Object);
    virtual void Destroy();

public:
    class CScene* GetScene() const
    {
        return m_Scene;
    }

    class CGameObject* GetGameObject() const
    {
        return m_Object;
    }

protected:
    Component_Type  m_ComponentType;

public:
    Component_Type GetComponentType() const
    {
        return m_ComponentType;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime) = 0;
    virtual void PostUpdate(float DeltaTime) = 0;
    virtual void PrevRender() = 0;
    virtual void Render() = 0;
    virtual void PostRender() = 0;
    virtual CComponent* Clone() = 0;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

