#pragma once

#include "../Ref.h"
#include "../GameInfo.h"

class CSceneMode : 
	public CRef
{
	friend class CScene;
	friend class CSceneManager;

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
	virtual void SceneChangeComplete();
};

