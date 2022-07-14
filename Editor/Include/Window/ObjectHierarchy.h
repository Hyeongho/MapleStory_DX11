#pragma once

#include "IMGUIWindow.h"
#include "GameObject/GameObject.h"
#include "Component/SceneComponent.h"

class CObjectHierarchy :
	public CIMGUIWindow
{
public:
	CObjectHierarchy();
	virtual ~CObjectHierarchy();

private:
	class CIMGUIListBox* m_ObjectListWidget;
	class CIMGUIListBox* m_ComponentListWidget;
	CSharedPtr<CGameObject> m_SelectObject;
	CSharedPtr<CGameObject> m_PrevObject;
	CSharedPtr<CSceneComponent> m_SelectComponent;

public:
	class CIMGUIListBox* GetObjectList() const
	{
		return m_ObjectListWidget;
	}

	class CIMGUIListBox* GetComponentList()	const
	{
		return m_ComponentListWidget;
	}

	CGameObject* GetSelectObject() const
	{
		return m_SelectObject;
	}

	CSceneComponent* GetSelectComponent() const
	{
		return m_SelectComponent;
	}

public:
	void AddObjectList(const char* Name);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void SelectObject(int Index, const char* Item);
	void SelectComponent(int Index, const char* Item);
};

