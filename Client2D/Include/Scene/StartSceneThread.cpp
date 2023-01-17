#include "StartSceneThread.h"
#include "Scene/SceneManager.h"
#include "StartScene.h"

CStartSceneThread::CStartSceneThread()
{
}

CStartSceneThread::~CStartSceneThread()
{
}

bool CStartSceneThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CStartSceneThread::Run()
{
	// ·Îµù

	CSceneManager::GetInst()->CreateNextScene(false);
	/*CSeolHuibang* SeolHuibang = CSceneManager::GetInst()->CreateSceneModeEmpty<CSeolHuibang>(false);

	SeolHuibang->SetLoadingFunction<CSeolHuiThread>(this, &CSeolHuiThread::AddMessage);

	SeolHuibang->Init();*/

	CSceneManager::GetInst()->CreateSceneMode<CStartScene>(false);

	AddMessage(true, 1.f);
}
