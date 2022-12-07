#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CJr_BalrogAttack2Ball :
    public CGameObject
{
public:
	CJr_BalrogAttack2Ball();
	CJr_BalrogAttack2Ball(const CJr_BalrogAttack2Ball& obj);
	virtual ~CJr_BalrogAttack2Ball();

private:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Body;

	CAnimationSequence2DInstance* m_Anim;

	float m_Distance;
	float m_Direction;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CJr_BalrogAttack2Ball* Clone();

public:
	void SetFlip(bool Flip);
	void SetDirection(float Direction)
	{
		m_Direction = Direction;
	}

protected:
	virtual void AnimationFinish();

private:
	void CollisionCallbackBegin(const CollisionResult& result);
};

