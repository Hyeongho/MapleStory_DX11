#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CBodyAttack3Hit :
    public CGameObject
{
public:
	CBodyAttack3Hit();
	CBodyAttack3Hit(const CBodyAttack3Hit& obj);
	virtual ~CBodyAttack3Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBodyAttack3Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

