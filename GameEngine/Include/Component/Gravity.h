#pragma once

#include "ObjectComponent.h"
#include "../GameInfo.h"

class CGravity :
    public CObjectComponent
{
	friend class CGameObject;

private:
	CGravity();
	CGravity(const CGravity& com);
	virtual ~CGravity();

private:
	CSharedPtr<class CSceneComponent> m_UpdateComponent;

private:
	bool m_Ground;

public:
	void SetUpdateComponent(class CSceneComponent* UpdateComponent);

public:
	void SetGround(bool Ground)
	{
		m_Ground = Ground;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CGravity* Clone();
};

