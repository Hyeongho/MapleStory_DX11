#include "Viewport.h"
#include "../Input.h"

CViewport::CViewport()
{
}

CViewport::~CViewport()
{
}

void CViewport::Start()
{
	auto iter = m_WindowList.begin();
	auto iterEnd = m_WindowList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Start();
	}
}

bool CViewport::Init()
{
	return true;
}

void CViewport::Update(float DeltaTime)
{
	auto iter = m_WindowList.begin();
	auto iterEnd = m_WindowList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WindowList.erase(iter);
			iterEnd = m_WindowList.end();
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

void CViewport::PostUpdate(float DeltaTime)
{
	auto iter = m_WindowList.begin();
	auto iterEnd = m_WindowList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WindowList.erase(iter);
			iterEnd = m_WindowList.end();
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

bool CViewport::CollisionMouse()
{
	Vector2 MousePos = CInput::GetInst()->GetMousePos();

	// 출력 우선순위가 높은 위젯부터 충돌처리를 시작한다.
	if (m_WindowList.size() >= 2)
	{
		m_WindowList.sort(CViewport::SortWindow);
	}

	auto iter = m_WindowList.begin();
	auto iterEnd = m_WindowList.end();

	for (; iter != iterEnd; iter++)
	{
		if (!(*iter)->GetVisibility())
		{
			continue;
		}

		if (!(*iter)->IsEnable())
		{
			continue;
		}

		if ((*iter)->CollisionMouse(MousePos))
		{
			return true;
		}
	}

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WindowList.erase(iter);
			iterEnd = m_WindowList.end();
			continue;
		}

		iter++;
	}

	return false;
}

void CViewport::Collision()
{
	auto iter = m_WindowList.begin();
	auto iterEnd = m_WindowList.end();

	for (; iter != iterEnd; iter++)
	{
		if (!(*iter)->GetVisibility())
		{
			continue;
		}

		if (!(*iter)->IsEnable())
		{
			continue;
		}
	}

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WindowList.erase(iter);
			iterEnd = m_WindowList.end();
			continue;
		}

		iter++;
	}
}

void CViewport::Render()
{
	auto iter = m_WindowList.rbegin();
	auto iterEnd = m_WindowList.rend();

	for (; iter != iterEnd; iter++)
	{
		if (!(*iter)->GetVisibility())
		{
			continue;
		}

		(*iter)->Render();
	}
}

bool CViewport::SortWindow(CSharedPtr<CWidgetWindow> Src, CSharedPtr<CWidgetWindow> Dest)
{
	return Src->GetZOrder() > Dest->GetZOrder();
}
