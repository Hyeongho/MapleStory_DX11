#include "LoadingThread.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"

CLoadingThread::CLoadingThread()
{
}

CLoadingThread::~CLoadingThread()
{
}

bool CLoadingThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CLoadingThread::Run()
{
	// ·Îµù
	CSceneManager::GetInst()->CreateNextScene(false);
	CMainScene* MainScene = CSceneManager::GetInst()->CreateSceneModeEmpty<CMainScene>(false);

	MainScene->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);

	MainScene->Init();

	AddMessage(true, 1.f);
}
