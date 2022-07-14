#pragma once

#include "../Ref.h"
#include "Widget.h"

class CWidgetWindow :
    public CRef
{
	friend class CViewport;
	friend class CWidgetComponent;
	friend class CEngine;

protected:
	CWidgetWindow();
	CWidgetWindow(const CWidgetWindow& window);
	virtual ~CWidgetWindow();

protected:
	class CWidgetComponent* m_OwnerComponent;
	class CViewport* m_Viewport;
	int m_ZOrder;
	bool m_Visibility;
	Vector2 m_Pos;
	Vector2 m_Size;
	bool m_Start;	

	std::list<CSharedPtr<CWidget>> m_WidgetList;

public:
	class CWidgetComponent* GetWidgetComponent() const
	{
		return m_OwnerComponent;
	}

	class CViewport* GetViewport() const
	{
		return m_Viewport;
	}

	int GetWidgetCount() const
	{
		return (int)m_WidgetList.size();
	}

	Vector2 GetWindowPos() const
	{
		return m_Pos;
	}

	Vector2 GetWindowSize() const
	{
		return m_Size;
	}

	int GetZOrder()	const
	{
		return m_ZOrder;
	}

	bool GetVisibility() const
	{
		return m_Visibility;
	}

public:
	void SetZOrder(int ZOrder)
	{
		m_ZOrder = ZOrder;
	}

	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetPos(float x, float y)
	{
		m_Pos = Vector2(x, y);
	}

	void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	void SetSize(float x, float y)
	{
		m_Size = Vector2(x, y);
	}

	void SetVisibility(bool Visibility)
	{
		m_Visibility = Visibility;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual bool CollisionMouse(const Vector2& MousePos);
	virtual CWidgetWindow* Clone();

private:
	static bool SortWidget(CSharedPtr<CWidget> Src, CSharedPtr<CWidget> Dest);

public:
	template <typename T>
	T* FindWidget(const std::string& Name)
	{
		auto iter = m_WidgetList.begin();
		auto iterEnd = m_WidgetList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
			{
				return (T*)*(*iter);
			}
		}

		return nullptr;
	}

	template <typename T>
	T* CreateWidget(const std::string& Name)
	{
		T* Widget = new T;

		Widget->SetName(Name);
		Widget->SetOwner(this);

		if (!Widget->Init())
		{
			SAFE_RELEASE(Widget);
			return nullptr;
		}

		m_WidgetList.push_back((CWidget*)Widget);

		return Widget;
	}
};

