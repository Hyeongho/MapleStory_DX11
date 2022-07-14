#pragma once

#include "../GameInfo.h"
#include "../Component/CameraComponent.h"

class CCameraManager
{
	friend class CScene;

private:
	CCameraManager();
	~CCameraManager();

private:
	class CScene* m_Scene;

private:
	CSharedPtr<CCameraComponent> m_CurrentCamera;
	CSharedPtr<CCameraComponent> m_KeepCamera;
	CSharedPtr<CCameraComponent> m_UICamera;

public:
	CCameraComponent* GetCurrentCamera()	const
	{
		return m_CurrentCamera;
	}

	CCameraComponent* GetUICamera()	const
	{
		return m_UICamera;
	}

	void SetCurrentCamera(CCameraComponent* Camera)
	{
		m_CurrentCamera = Camera;
	}

	void KeepCamera()
	{
		m_KeepCamera = m_CurrentCamera;
	}

	void ReturnCamera()
	{
		m_CurrentCamera = m_KeepCamera;

		m_KeepCamera = nullptr;
	}

public:
	void Start();
	void Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
};

