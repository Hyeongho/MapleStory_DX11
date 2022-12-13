#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CBodyAttack1Hit :
    public CGameObject
{
public:
	CBodyAttack1Hit();
	CBodyAttack1Hit(const CBodyAttack1Hit& obj);
	virtual ~CBodyAttack1Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBodyAttack1Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

