#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CJr_BalrogAttack1Hit :
    public CGameObject
{
public:
	CJr_BalrogAttack1Hit();
	CJr_BalrogAttack1Hit(const CJr_BalrogAttack1Hit& obj);
	virtual ~CJr_BalrogAttack1Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CJr_BalrogAttack1Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

