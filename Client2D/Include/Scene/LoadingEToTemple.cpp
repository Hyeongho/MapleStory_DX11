#include "LoadingEToTemple.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "EToTempleThread.h"
#include "Scene/SceneManager.h"
#include "../Object/PlayerManager.h"

CLoadingEToTemple::CLoadingEToTemple()
{
	SetTypeID<CLoadingEToTemple>();
}

CLoadingEToTemple::~CLoadingEToTemple()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingEToTemple::Init()
{
	//m_LoadingWidget = m_Scene->GetViewport()->CreateWidgetWindow<CLoadingWidget>("LoadingWidget");

	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CEToTempleThread>("EToTempleThread");

	m_LoadingThread->Start();

	return true;
}

void CLoadingEToTemple::Update(float DeltaTime)
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

			CPlayerManager::GetInst()->SetTagPotal(false);
		}
	}
}
