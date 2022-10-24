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

	CSceneManager::GetInst()->CreateNextScene(false);
	/*CSeolhuiuibang* Seolhuiuibang = CSceneManager::GetInst()->CreateSceneModeEmpty<CSeolhuiuibang>(false);

	Seolhuiuibang->SetLoadingFunction<CSeolhuiuiThread>(this, &CSeolhuiuiThread::AddMessage);

	Seolhuiuibang->Init();*/

	CSceneManager::GetInst()->CreateSceneMode<CSeolhuiuibang>(false);

	AddMessage(true, 1.f);
}
