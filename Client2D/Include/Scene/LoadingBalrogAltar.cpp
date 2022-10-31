#include "LoadingBalrogAltar.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "BalrogAltarThread.h"
#include "Scene/SceneManager.h"
#include "../Object/PlayerManager.h"

CLoadingBalrogAltar::CLoadingBalrogAltar()
{
	SetTypeID<CLoadingBalrogAltar>();
}

CLoadingBalrogAltar::~CLoadingBalrogAltar()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingBalrogAltar::Init()
{
	return true;
}

void CLoadingBalrogAltar::Update(float DeltaTime)
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

void CLoadingBalrogAltar::SceneChangeComplete()
{
	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CBalrogAltarThread>("BalrogAltarThread");

	m_LoadingThread->Start();
}
