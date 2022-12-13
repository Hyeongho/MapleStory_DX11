#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CRightAttack1Hit :
    public CGameObject
{
public:
	CRightAttack1Hit();
	CRightAttack1Hit(const CRightAttack1Hit& obj);
	virtual ~CRightAttack1Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CRightAttack1Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

