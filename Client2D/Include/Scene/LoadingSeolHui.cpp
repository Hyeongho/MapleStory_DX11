#include "LoadingSeolHui.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "SeolHuiThread.h"
#include "Scene/SceneManager.h"
#include "../Object/PlayerManager.h"

CLoadingSeolHui::CLoadingSeolHui()
{
	SetTypeID<CLoadingSeolHui>();
}

CLoadingSeolHui::~CLoadingSeolHui()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingSeolHui::Init()
{
	//m_LoadingWidget = m_Scene->GetViewport()->CreateWidgetWindow<CLoadingWidget>("LoadingWidget");

	// 로딩 스레드 생성
	/*m_LoadingThread = CThread::CreateThread<CSeolHuiThread>("SeolHuiThread");

	m_LoadingThread->Start();*/

	return true;
}

void CLoadingSeolHui::Update(float DeltaTime)
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

void CLoadingSeolHui::SceneChangeComplete()
{
	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CSeolHuiThread>("SeolHuiThread");

	m_LoadingThread->Start();
}
