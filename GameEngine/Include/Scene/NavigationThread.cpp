#include "NavigationThread.h"
#include "Navigation.h"
#include "NavigationManager.h"

CNavigationThread::CNavigationThread()
{
	SetLoop(true);

	m_Navigation = new CNavigation;

	m_ExitEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

CNavigationThread::~CNavigationThread()
{
	m_Loop = false;

	WaitForSingleObject(m_ExitEvent, INFINITE);

	CloseHandle(m_ExitEvent);

	SAFE_DELETE(m_Navigation);
}

void CNavigationThread::CreateNavigationNode(CTileMapComponent* TileMap)
{
	m_Navigation->CreateNavigationNode(TileMap);
}

void CNavigationThread::Run()
{
	while (m_Loop)
	{
		if (!m_WorkQueue.empty())
		{
			NavWorkData Work = m_WorkQueue.front();
			m_WorkQueue.pop();

			NavResultData Result;

			m_Navigation->FindPath(Work.OwnerComponent->GetWorldPos(), Work.End, Result.vecPath);

			Result.Callback = Work.Callback;

			m_NavManager->AddNavResult(Result);
		}
	}

	SetEvent(m_ExitEvent);
}
