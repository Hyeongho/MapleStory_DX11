#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CJr_BalrogAttack3Hit :
    public CGameObject
{
public:
	CJr_BalrogAttack3Hit();
	CJr_BalrogAttack3Hit(const CJr_BalrogAttack3Hit& obj);
	virtual ~CJr_BalrogAttack3Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CJr_BalrogAttack3Hit* Clone();

protected:
	virtual void AnimationFinish();
};

