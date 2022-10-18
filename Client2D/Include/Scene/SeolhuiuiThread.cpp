#include "SeolhuiuiThread.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"
#include "Seolhuiuibang.h"

CSeolhuiuiThread::CSeolhuiuiThread()
{
}

CSeolhuiuiThread::~CSeolhuiuiThread()
{
}

bool CSeolhuiuiThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CSeolhuiuiThread::Run()
{
	// ·Îµù
	Sleep(1000);

	CSceneManager::GetInst()->CreateNextScene(false);
	CSeolhuiuibang* Seolhuiuibang = CSceneManager::GetInst()->CreateSceneModeEmpty<CSeolhuiuibang>(false);

	Seolhuiuibang->SetLoadingFunction<CSeolhuiuiThread>(this, &CSeolhuiuiThread::AddMessage);

	Seolhuiuibang->Init();

	AddMessage(true, 1.f);
}
