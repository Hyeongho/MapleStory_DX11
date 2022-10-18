#include "LoadingThread.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"
#include "TestScene.h"

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
	Sleep(1000);

	CSceneManager::GetInst()->CreateNextScene(false);
	CMainScene* MainScene = CSceneManager::GetInst()->CreateSceneModeEmpty<CMainScene>(false);

	MainScene->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);

	MainScene->Init();

	AddMessage(true, 1.f);
}
