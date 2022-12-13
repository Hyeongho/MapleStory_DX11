#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CRightAttack3Hit :
    public CGameObject
{
public:
	CRightAttack3Hit();
	CRightAttack3Hit(const CRightAttack3Hit& obj);
	virtual ~CRightAttack3Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CRightAttack3Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

