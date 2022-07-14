#pragma once

#include "GameObject/GameObject.h"
#include "Component/CameraComponent.h"
#include "Component/SpriteComponent.h"

class CCameraObject :
    public CGameObject
{
    friend class CScene;

protected:
    CCameraObject();
    CCameraObject(const CCameraObject& obj);
    virtual ~CCameraObject();

private:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<class CStaticMeshComponent> m_Mesh;
    CSharedPtr<CCameraComponent> m_Camera;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CCameraObject* Clone();
};

