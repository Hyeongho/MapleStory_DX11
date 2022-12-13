#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CRightAttack2Hit :
    public CGameObject
{
public:
	CRightAttack2Hit();
	CRightAttack2Hit(const CRightAttack2Hit& obj);
	virtual ~CRightAttack2Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CRightAttack2Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

