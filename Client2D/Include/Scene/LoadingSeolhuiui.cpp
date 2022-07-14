#include "LoadingSeolhuiui.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "SeolhuiuiThread.h"
#include "Scene/SceneManager.h"
#include "../Object/PlayerManager.h"

CLoadingSeolhuiui::CLoadingSeolhuiui()
{
	SetTypeID<CLoadingSeolhuiui>();
}

CLoadingSeolhuiui::~CLoadingSeolhuiui()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingSeolhuiui::Init()
{
	//m_LoadingWidget = m_Scene->GetViewport()->CreateWidgetWindow<CLoadingWidget>("LoadingWidget");

	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CSeolhuiuiThread>("SeolhuiuiThread");

	m_LoadingThread->Start();

	return true;
}

void CLoadingSeolhuiui::Update(float DeltaTime)
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