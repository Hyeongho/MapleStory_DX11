#pragma once

#include "ObjectComponent.h"

class CNavAgent :
	public CObjectComponent
{
	friend class CGameObject;

protected:
	CNavAgent();
	CNavAgent(const CNavAgent& com);
	virtual ~CNavAgent();

private:
	CSharedPtr<class CSceneComponent> m_UpdateComponent;
	std::list<Vector3> m_PathList;
	float m_MoveSpeed;

public:
	void SetUpdateComponent(class CSceneComponent* UpdateComponent);
	bool Move(const Vector3& EndPos);
	void SetMoveSpeed(float Speed)
	{
		m_MoveSpeed = Speed;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CNavAgent* Clone();

private:
	void PathResult(const std::list<Vector3>& PathList);
};

