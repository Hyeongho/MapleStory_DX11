#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CLeftAttack2Hit :
    public CGameObject
{
public:
	CLeftAttack2Hit();
	CLeftAttack2Hit(const CLeftAttack2Hit& obj);
	virtual ~CLeftAttack2Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CLeftAttack2Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

