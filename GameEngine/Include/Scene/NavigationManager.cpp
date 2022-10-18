#include "NavigationManager.h"

CNavigationManager::CNavigationManager()
{
}

CNavigationManager::~CNavigationManager()
{
	size_t Size = m_vecNavigationThread.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecNavigationThread[i]);
	}

	m_vecNavigationThread.clear();
}

void CNavigationManager::SetNavData(CTileMapComponent* NavData)
{
	m_NavData = NavData;

	if (!m_vecNavigationThread.empty())
	{
		size_t Size = m_vecNavigationThread.size();

		for (size_t i = 0; i < Size; i++)
		{
			SAFE_DELETE(m_vecNavigationThread[i]);
		}

		m_vecNavigationThread.clear();
	}

	if (m_NavData)
	{
		for (int i = 0; i < 4; i++)
		{
			char Name[256] = {};
			sprintf_s(Name, "Thread%d", i);
			CNavigationThread* Thread = CThread::CreateThread<CNavigationThread>(Name);

			Thread->m_NavManager = this;
			Thread->CreateNavigationNode(m_NavData);

			Thread->Start();

			m_vecNavigationThread.push_back(Thread);
		}
	}
}

void CNavigationManager::AddNavResult(const NavResultData& NavData)
{
	m_ResultQueue.push(NavData);
}

void CNavigationManager::Start()
{
}

bool CNavigationManager::Init()
{
	return true;
}

void CNavigationManager::Update(float DeltaTime)
{
	if (!m_ResultQueue.empty())
	{
		NavResultData Result = m_ResultQueue.front();
		m_ResultQueue.pop();

		Result.Callback(Result.vecPath);
	}
}
