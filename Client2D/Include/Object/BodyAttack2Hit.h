#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CBodyAttack2Hit :
    public CGameObject
{
public:
	CBodyAttack2Hit();
	CBodyAttack2Hit(const CBodyAttack2Hit& obj);
	virtual ~CBodyAttack2Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBodyAttack2Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

