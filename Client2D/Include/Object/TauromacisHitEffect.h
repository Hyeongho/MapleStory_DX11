#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

class CTauromacisHitEffect :
    public CGameObject
{
public:
	CTauromacisHitEffect();
	CTauromacisHitEffect(const CTauromacisHitEffect& obj);
	virtual ~CTauromacisHitEffect();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTauromacisHitEffect* Clone();

protected:
	virtual void AnimationFinish();
};

