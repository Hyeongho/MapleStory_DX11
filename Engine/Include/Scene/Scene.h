#pragma once

#include "SceneMode.h"
#include "SceneResource.h"
#include "SceneCollision.h"
#include "CameraManager.h"
#include "Viewport.h"
#include "NavigationManager.h"
#include "../GameObject/GameObject.h"

class CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	CSharedPtr<CSceneMode> m_Mode;
	//CSceneMode* m_Mode;
	CSceneResource* m_Resource;
	CSceneCollision* m_Collision;
	CCameraManager* m_CameraManager;
	CViewport* m_Viewport;
	CNavigationManager* m_NavManager;
	std::list<CSharedPtr<CGameObject>> m_ObjList;

	std::unordered_map<std::string, CSharedPtr<CGameObject>> m_mapPrototype;
	std::list<CSharedPtr<CGameObject>> m_PrototypeList;

	bool m_Start;
	bool m_Change;

	Project_Type m_ProjectType;

public:
	void SetAutoChange(bool Change)
	{
		m_Change = Change;
	}

	void SetProjectType(Project_Type ProjectType)
	{
		m_ProjectType = ProjectType;
	}

	Project_Type GetProjectType() const
	{
		return m_ProjectType;
	}

	CSceneMode* GetSceneMode() const
	{
		return m_Mode;
	}

public:
	std::list<CSharedPtr<CGameObject>> GetObjList()
	{
		return m_ObjList;
	}

	CSceneResource* GetResource() const
	{
		return m_Resource;
	}

	CSceneCollision* GetCollision() const
	{
		return m_Collision;
	}

	CCameraManager* GetCameraManager() const
	{
		return m_CameraManager;
	}

	CViewport* GetViewport() const
	{
		return m_Viewport;
	}

	CNavigationManager* GetNavigationManager() const
	{
		return m_NavManager;
	}

	CGameObject* GetPlayerObject() const
	{
		return m_Mode->GetPlayerObject();
	}

	CGameObject* FindObject(const std::string& Name)
	{
		auto iter = m_ObjList.begin();
		auto iterEnd = m_ObjList.end();

		for (; iter != iterEnd; iter++)
		{
			if ((*iter)->GetName() == Name)
			{
				return *iter;
			}
		}

		return nullptr;
	}

public:
	void Start();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Save(const char* FileName, const std::string& PathName = SCENE_PATH);
	void SaveFullPath(const char* FullPath);
	void Load(const char* FileName, const std::string& PathName = SCENE_PATH);
	void LoadFullPath(const char* FullPath);
	void SceneChangeComplete();

private:
	CGameObject* FindPrototype(const std::string& Name);

public:
	template <typename T>
	bool CreateSceneMode()
	{
		m_Mode = new T;

		m_Mode->m_Scene = this;

		if (!m_Mode->Init())
		{
			m_Mode = nullptr;
			return false;
		}

		return true;
	}

	template <typename T>
	T* CreateSceneModeEmpty()
	{
		m_Mode = new T;

		m_Mode->m_Scene = this;

		return (T*)*m_Mode;
	}

	template <typename T>
	bool LoadSceneMode()
	{
		m_Mode = new T;

		m_Mode->m_Scene = this;
		
		return true;
	}

	template <typename T>
	T* CreateGameObject(const std::string& Name)
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->SetScene(this);

		if (!Obj->Init())
		{
			SAFE_RELEASE(Obj);
			return nullptr;
		}

		m_ObjList.push_back(Obj);

		if (m_Start)
		{
			Obj->Start();
		}

		return Obj;
	}

	template <typename T>
	T* LoadGameObject()
	{
		T* Obj = new T;

		Obj->SetScene(this);

		m_ObjList.push_back(Obj);

		if (m_Start)
		{
			Obj->Start();
		}

		return Obj;
	}

	template <typename T>
	T* CreatePrototype(const std::string& Name)
	{
		T* Obj = new T;

		Obj->SetScene(this);
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		m_mapPrototype.insert(std::make_pair(Name, Obj));

		return Obj;
	}

	template <typename T>
	T* CreateGameObject(const std::string Name, const std::string& PrototypeName, const Vector2& Pos = Vector2(0.f, 0.f), const Vector2 Size = Vector2(100.f, 100.f))
	{
		CGameObject* Prototype = FindPrototype(PrototypeName);

		if (!Prototype)
		{
			return nullptr;
		}

		T* Obj = dynamic_cast<T*>(Prototype->Clone());

		Obj->SetScene(this);
		Obj->SetPos(Pos);
		Obj->SetSize(Size);
		Obj->SetName(Name);

		m_PrototypeList.push_back(Obj);

		return Obj;
	}
};

