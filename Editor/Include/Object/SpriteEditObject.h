#pragma once

#include "GameObject/GameObject.h"

class CSpriteEditObject :
    public CGameObject
{
    friend class CScene;

protected:
    CSpriteEditObject();
    CSpriteEditObject(const CSpriteEditObject& obj);
    virtual ~CSpriteEditObject();

private:
    CSharedPtr<class CSpriteComponent> m_Sprite;
    float m_Distance;

public:
    class CSpriteComponent* GetSpriteComponent() const
    {
        return m_Sprite;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CSpriteEditObject* Clone();
};

