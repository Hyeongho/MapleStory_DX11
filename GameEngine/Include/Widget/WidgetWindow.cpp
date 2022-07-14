#include "WidgetWindow.h"
#include "../Component/WidgetComponent.h"
#include "../Scene/Scene.h"

CWidgetWindow::CWidgetWindow() : m_Viewport(nullptr), m_OwnerComponent(nullptr), m_ZOrder(0), m_Size(100.f, 100.f), m_Start(false), m_Visibility(true)
{
}

CWidgetWindow::CWidgetWindow(const CWidgetWindow& window)
{
	*this = window;
	m_OwnerComponent = nullptr;

	auto iter = window.m_WidgetList.begin();
	auto iterEnd = window.m_WidgetList.end();

	m_WidgetList.clear();

	for (; iter != iterEnd; iter++)
	{
		CWidget* Widget = (*iter)->Clone();

		Widget->m_Owner = this;

		m_WidgetList.push_back(Widget);
	}
}

CWidgetWindow::~CWidgetWindow()
{
}

void CWidgetWindow::Start()
{
	m_Start = true;

	auto iter = m_WidgetList.begin();
	auto iterEnd = m_WidgetList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Start();
	}

	if (m_OwnerComponent)
	{
		m_Viewport = m_OwnerComponent->GetScene()->GetViewport();
	}
}

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float DeltaTime)
{
	if (!m_Start)
	{
		Start();
	}

	auto iter = m_WidgetList.begin();
	auto iterEnd = m_WidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WidgetList.erase(iter);
			iterEnd = m_WidgetList.end();
			continue;
		}

		else if (!(*iter)->GetVisibility())
		{
			iter++;
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Update(DeltaTime);
		iter++;
	}
}

void CWidgetWindow::PostUpdate(float DeltaTime)
{
	if (!m_Start)
	{
		Start();
	}

	auto iter = m_WidgetList.begin();
	auto iterEnd = m_WidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WidgetList.erase(iter);
			iterEnd = m_WidgetList.end();
			continue;
		}

		else if (!(*iter)->GetVisibility())
		{
			iter++;
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		iter++;
	}
}

void CWidgetWindow::Render()
{
	if (!m_Start)
	{
		Start();
	}

	auto iter = m_WidgetList.begin();
	auto iterEnd = m_WidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WidgetList.erase(iter);
			iterEnd = m_WidgetList.end();
			continue;
		}

		else if (!(*iter)->GetVisibility())
		{
			iter++;
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Render();
		iter++;
	}
}

bool CWidgetWindow::CollisionMouse(const Vector2& MousePos)
{
	m_WidgetList.sort(CWidgetWindow::SortWidget);

	// 윈도우 영역 안에 들어오는지 판단한다.
	if (m_Pos.x > MousePos.x)
	{
		return false;
	}

	else if (m_Pos.x + m_Size.x < MousePos.x)
	{
		return false;
	}

	else if (m_Pos.y > MousePos.y)
	{
		return false;
	}

	else if (m_Pos.y + m_Size.y < MousePos.y)
	{
		return false;
	}

	auto iter = m_WidgetList.rbegin();
	auto iterEnd = m_WidgetList.rend();

	for (; iter != iterEnd; ++iter)
	{
		if (!(*iter)->IsEnable())
		{
			continue;
		}

		if ((*iter)->CollisionMouse(MousePos))
		{
			(*iter)->m_MouseHovered = true;
			return true;
		}

		else
		{
			(*iter)->m_MouseHovered = false;
		}
	}

	return false;
}

CWidgetWindow* CWidgetWindow::Clone()
{
	return new CWidgetWindow(*this);
}

bool CWidgetWindow::SortWidget(CSharedPtr<CWidget> Src, CSharedPtr<CWidget> Dest)
{
	return Src->GetZOrder() < Dest->GetZOrder();
}
