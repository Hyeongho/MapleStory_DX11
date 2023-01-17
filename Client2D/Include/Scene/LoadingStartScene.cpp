#include "LoadingStartScene.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "StartSceneThread.h"
#include "Scene/SceneManager.h"
#include "../Object/PlayerManager.h"

CLoadingStartScene::CLoadingStartScene()
{
	SetTypeID<CLoadingStartScene>();
}

CLoadingStartScene::~CLoadingStartScene()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingStartScene::Init()
{
	return true;
}

void CLoadingStartScene::Update(float DeltaTime)
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

void CLoadingStartScene::SceneChangeComplete()
{
	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CStartSceneThread>("SeolHuiThread");

	m_LoadingThread->Start();
}
