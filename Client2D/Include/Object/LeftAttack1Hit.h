#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CLeftAttack1Hit :
    public CGameObject
{
public:
	CLeftAttack1Hit();
	CLeftAttack1Hit(const CLeftAttack1Hit& obj);
	virtual ~CLeftAttack1Hit();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CLeftAttack1Hit* Clone();

public:
	void SetFlip(bool Flip);

protected:
	virtual void AnimationFinish();
};

