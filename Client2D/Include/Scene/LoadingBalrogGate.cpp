#include "LoadingBalrogGate.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "BalrogGateThread.h"
#include "Scene/SceneManager.h"
#include "../Object/PlayerManager.h"

CLoadingBalrogGate::CLoadingBalrogGate()
{
	SetTypeID<CLoadingBalrogGate>();
}

CLoadingBalrogGate::~CLoadingBalrogGate()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingBalrogGate::Init()
{
	return true;
}

void CLoadingBalrogGate::Update(float DeltaTime)
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

void CLoadingBalrogGate::SceneChangeComplete()
{
	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CBalrogGateThread>("BalrogGateThread");

	m_LoadingThread->Start();
}
