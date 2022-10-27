#include "SeolHuiThread.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"
#include "SeolHuibang.h"

CSeolHuiThread::CSeolHuiThread()
{
}

CSeolHuiThread::~CSeolHuiThread()
{
}

bool CSeolHuiThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CSeolHuiThread::Run()
{
	// ·Îµù

	CSceneManager::GetInst()->CreateNextScene(false);
	/*CSeolHuibang* SeolHuibang = CSceneManager::GetInst()->CreateSceneModeEmpty<CSeolHuibang>(false);

	SeolHuibang->SetLoadingFunction<CSeolHuiThread>(this, &CSeolHuiThread::AddMessage);

	SeolHuibang->Init();*/

	CSceneManager::GetInst()->CreateSceneMode<CSeolHuibang>(false);

	AddMessage(true, 1.f);
}
