#include "LoadingAnotherDoor.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "AnotherDoorThread.h"
#include "Scene/SceneManager.h"
#include "../Object/PlayerManager.h"

CLoadingAnotherDoor::CLoadingAnotherDoor()
{
	SetTypeID<CLoadingAnotherDoor>();
}

CLoadingAnotherDoor::~CLoadingAnotherDoor()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingAnotherDoor::Init()
{
	//m_LoadingWidget = m_Scene->GetViewport()->CreateWidgetWindow<CLoadingWidget>("LoadingWidget");

	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CAnotherDoorThread>("AnotherDoorThread");

	m_LoadingThread->Start();

	return true;
}

void CLoadingAnotherDoor::Update(float DeltaTime)
{
	CSceneMode::Update(DeltaTime);

	CThreadQueue<LoadingMessage>* Queue = m_LoadingThread->GetLoadingQueue();

	if (!Queue->empty())
	{
		LoadingMessage Msg = Queue->front();

		Queue->pop();

		//m_LoadingWidget->SetLoadingPercent(Msg.Percent);

		if (Msg.Complete)
		{
			CSceneManager::GetInst()->ChangeNextScene();
		}
	}
}

void CLoadingAnotherDoor::SceneChangeComplete()
{
}
