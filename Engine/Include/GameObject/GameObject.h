#pragma once

#include "../Component/SceneComponent.h"
#include "../Component/ObjectComponent.h"

class CGameObject :
    public CRef
{
    friend class CScene;

protected:
    CGameObject();
    CGameObject(const CGameObject& obj);
    virtual ~CGameObject();

protected:
    class CScene* m_Scene;

public:
    class CScene* GetScene() const
    {
        return m_Scene;
    }

public:
    void SetScene(class CScene* Scene);
	virtual void Destroy();

protected:
    CSharedPtr<CSceneComponent> m_RootComponent;
	std::list<CSceneComponent*>	m_SceneComponentList;
    std::vector<CSharedPtr<CObjectComponent>> m_vecObjectComponent;

	CGameObject* m_Parent;
	std::vector<CSharedPtr<CGameObject>> m_vecChildObject;

	Vector3 m_PrevPos;

public:
    void SetRootComponent(CSceneComponent* Component)
    {
        m_RootComponent = Component;
    }

	CSceneComponent* GetRootComponent()	const
	{
		return m_RootComponent;
	}

	void AddSceneComponent(CSceneComponent* Component)
	{
		m_SceneComponentList.push_back(Component);
	}

	class CComponent* FindComponent(const std::string& Name);
	template <typename T>
	T* FindComponentFromType()
	{
		auto iter = m_SceneComponentList.begin();
		auto iterEnd = m_SceneComponentList.end();

		for (; iter != iterEnd; iter++)
		{
			if ((*iter)->CheckType<T>())
			{
				return (T*)*iter;
			}
		}

		return nullptr;
	}
	void GetAllSceneComponentsName(std::vector<FindComponentName>& vecNames);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
	void AddCollision();
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CGameObject* Clone();
	//virtual float SetDamage(float Damage);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void Save(const char* FullPath);
	virtual void Load(const char* FullPath);
	virtual void Save(const char* FileName, const std::string& PathName);
	virtual void Load(const char* FileName, const std::string& PathName);

public:
	// NavAgent가 있을 경우에 동작한다.
	void Move(const Vector3& EndPos);

public:
    template <typename T>
    T* CreateComponent(const std::string& Name)
    {
		T* Component = new T;

		Component->SetName(Name);
		Component->SetScene(m_Scene);
		Component->SetGameObject(this);

		if (!Component->Init())
		{
			SAFE_RELEASE(Component);
			return nullptr;
		}

		if (Component->GetComponentType() == Component_Type::ObjectComponent)
		{
			m_vecObjectComponent.push_back((class CObjectComponent*)Component);
		}

		else
		{
			m_SceneComponentList.push_back((class CSceneComponent*)Component);

			if (!m_RootComponent)
			{
				m_RootComponent = Component;
			}
		}

		return Component;
    }

	template <typename T>
	T* LoadComponent()
	{
		T* Component = new T;

		Component->SetScene(m_Scene);
		Component->SetGameObject(this);

		if (Component->GetComponentType() == Component_Type::ObjectComponent)
		{
			m_vecObjectComponent.push_back((class CObjectComponent*)Component);
		}

		else
		{
			m_SceneComponentList.push_back((class CSceneComponent*)Component);

			if (!m_RootComponent)
			{
				m_RootComponent = Component;
			}
		}

		return Component;
	}

public:	// =============== 저주받은 Transform 영역 ===============
	void SetInheritScale(bool Inherit)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetInheritScale(Inherit);
	}

	void SetInheritRotX(bool Inherit)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetInheritRotX(Inherit);
	}

	void SetInheritRotY(bool Inherit)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetInheritRotY(Inherit);
	}

	void SetInheritRotZ(bool Inherit)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetInheritRotZ(Inherit);
	}

	void SetInheritParentRotationPosX(bool Inherit)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetInheritParentRotationPosX(Inherit);
	}

	void SetInheritParentRotationPosY(bool Inherit)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetInheritParentRotationPosY(Inherit);
	}

	void SetInheritParentRotationPosZ(bool Inherit)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetInheritParentRotationPosZ(Inherit);
	}

	void InheritScale(bool Current)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->InheritScale(Current);
	}

	void InheritRotation(bool Current)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->InheritRotation(Current);
	}

	void InheritParentRotationPos(bool Current)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->InheritParentRotationPos(Current);
	}

	void InheritWorldScale(bool Current)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->InheritWorldScale(Current);
	}

	void InheritWorldRotation(bool Current)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->InheritWorldRotation(Current);
	}

public:
	Vector3 GetRelativeScale() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetRelativeScale();
	}

	Vector3 GetRelativeRot() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetRelativeRot();
	}

	Vector3 GetRelativePos() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetRelativePos();
	}

	Vector3 GetRelativeAxis(AXIS Axis)
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetRelativeAxis(Axis);
	}

public:
	void SetRelativeScale(const Vector3& Scale)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativeScale(Scale);
	}

	void SetRelativeScale(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativeScale(x, y, z);
	}

	void SetRelativeRotation(const Vector3& Rot)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativeRotation(Rot);
	}

	void SetRelativeRotation(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativeRotation(x, y, z);
	}

	void SetRelativeRotationX(float x)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativeRotationX(x);
	}

	void SetRelativeRotationY(float y)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativeRotationY(y);
	}

	void SetRelativeRotationZ(float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativeRotationZ(z);
	}

	void SetRelativePos(const Vector3& Pos)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativePos(Pos);
	}

	void SetRelativePos(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetRelativePos(x, y, z);
	}

	void AddRelativeScale(const Vector3& Scale)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativeScale(Scale);
	}

	void AddRelativeScale(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativeScale(x, y, z);
	}

	void AddRelativeRotation(const Vector3& Rot)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativeRotation(Rot);
	}

	void AddRelativeRotation(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativeRotation(x, y, z);
	}

	void AddRelativeRotationX(float x)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativeRotationX(x);
	}

	void AddRelativeRotationY(float y)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativeRotationY(y);
	}

	void AddRelativeRotationZ(float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativeRotationZ(z);
	}

	void AddRelativePos(const Vector3& Pos)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativePos(Pos);
	}

	void AddRelativePos(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddRelativePos(x, y, z);
	}

public:
	Vector3 GetWorldScale() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetWorldScale();
	}

	Vector3 GetWorldRot() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetWorldRot();
	}

	Vector3 GetWorldPos() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetWorldPos();
	}

	Vector3 GetPivot() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetPivot();
	}

	Vector3 GetMeshSize() const
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetMeshSize();
	}

	const Matrix& GetWorldMatrix() const
	{
		if (!m_RootComponent)
		{
			return Matrix();
		}

		return m_RootComponent->GetWorldMatrix();
	}

	Vector3 GetWorldAxis(AXIS Axis)
	{
		if (!m_RootComponent)
		{
			return Vector3();
		}

		return m_RootComponent->GetWorldAxis(Axis);
	}

public:
	void SetPivot(const Vector3& Pivot)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetPivot(Pivot);
	}

	void SetPivot(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetPivot(x, y, z);
	}

	void SetMeshSize(const Vector3& Size)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetMeshSize(Size);
	}

	void SetMeshSize(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetMeshSize(x, y, z);
	}

public:
	void SetWorldScale(const Vector3& Scale)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldScale(Scale);
	}

	void SetWorldScale(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldScale(x, y, z);
	}

	void SetWorldRotation(const Vector3& Rot)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldRotation(Rot);
	}

	void SetWorldRotation(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldRotation(x, y, z);
	}

	void SetWorldRotationX(float x)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldRotationX(x);
	}

	void SetWorldRotationY(float y)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldRotationY(y);
	}

	void SetWorldRotationZ(float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldRotationZ(z);
	}

	void SetWorldPos(const Vector3& Pos)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldPos(Pos);
	}

	void SetWorldPos(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->SetWorldPos(x, y, z);
	}

	void AddWorldScale(const Vector3& Scale)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldScale(Scale);
	}

	void AddWorldScale(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldScale(x, y, z);
	}

	void AddWorldRotation(const Vector3& Rot)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldRotation(Rot);
	}

	void AddWorldRotation(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldRotation(x, y, z);
	}

	void AddWorldRotationX(float x)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldRotationX(x);
	}

	void AddWorldRotationY(float y)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldRotationY(y);
	}

	void AddWorldRotationZ(float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldRotationZ(z);
	}

	void AddWorldPos(const Vector3& Pos)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldPos(Pos);
	}

	void AddWorldPos(float x, float y, float z)
	{
		if (!m_RootComponent)
		{
			return;
		}

		m_RootComponent->AddWorldPos(x, y, z);
	}
};

