#pragma once

#include "../Ref.h"

class CSceneMode :
	public CRef
{
	friend class CScene;

protected:
	CSceneMode();
	virtual ~CSceneMode();

protected:
	class CScene* m_Scene;
	CSharedPtr<class CGameObject> m_PlayerObject;

public:
	void SetPlayerObject(class CGameObject* Obj);

	class CGameObject* GetPlayerObject() const
	{
		return m_PlayerObject;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
};

