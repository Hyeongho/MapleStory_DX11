#pragma once

#include "../GameInfo.h"
#include "../Component/TileMapComponent.h"
#include "../ThreadQueue.h"
#include "NavigationThread.h"

class CNavigationManager
{
	friend class CScene;

private:
	CNavigationManager();
	~CNavigationManager();

private:
	class CScene* m_Scene;
	std::vector<CNavigationThread*>	m_vecNavigationThread;
	CSharedPtr<CTileMapComponent> m_NavData;
	CThreadQueue<NavResultData> m_ResultQueue;

public:
	void SetNavData(CTileMapComponent* NavData);
	void AddNavResult(const NavResultData& NavData);

public:
	void Start();
	bool Init();
	void Update(float DeltaTime);

public:
	template <typename T, typename ComponentType>
	bool FindPath(T* Obj, void(T::* Func)(const std::list<Vector3>&), ComponentType* OwnerComponent, const Vector3& End)
	{
		if (m_vecNavigationThread.empty())
		{
			return false;
		}

		int	Count = m_vecNavigationThread[0]->GetWorkCount();
		int	WorkIndex = 0;

		size_t Size = m_vecNavigationThread.size();

		for (size_t i = 1; i < Size; i++)
		{
			if (Count > m_vecNavigationThread[i]->GetWorkCount())
			{
				Count = m_vecNavigationThread[i]->GetWorkCount();
				WorkIndex = (int)i;
			}
		}

		m_vecNavigationThread[WorkIndex]->AddWork<T>(Obj, Func, OwnerComponent, End);

		return true;
	}
};

