#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CBodyAttack4Hit :
    public CGameObject
{
public:
	CBodyAttack4Hit();
	CBodyAttack4Hit(const CBodyAttack4Hit& obj);
	virtual ~CBodyAttack4Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBodyAttack4Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

