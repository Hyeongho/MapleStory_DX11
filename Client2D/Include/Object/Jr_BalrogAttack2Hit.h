#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CJr_BalrogAttack2Hit :
    public CGameObject
{
public:
	CJr_BalrogAttack2Hit();
	CJr_BalrogAttack2Hit(const CJr_BalrogAttack2Hit& obj);
	virtual ~CJr_BalrogAttack2Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CJr_BalrogAttack2Hit* Clone();

protected:
	virtual void AnimationFinish();
};

