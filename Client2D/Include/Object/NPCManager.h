#pragma once

#include "GameObject/GameObject.h"
#include "../ClientManager.h"

class CNPCManager :
    public CGameObject
{
public:
	CNPCManager();
	CNPCManager(const CNPCManager& obj);
	virtual ~CNPCManager();

protected:
	int m_ID;
	const TCHAR* m_NPCName;
	bool m_Click;

	bool m_Action;

protected:
	void Talk(int ID);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNPCManager* Clone();
};

