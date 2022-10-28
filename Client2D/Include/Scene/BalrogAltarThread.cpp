#include "BalrogAltarThread.h"
#include "BalrogAltar.h"
#include "Scene/SceneManager.h"

CBalrogAltarThread::CBalrogAltarThread()
{
}

CBalrogAltarThread::~CBalrogAltarThread()
{
}

bool CBalrogAltarThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CBalrogAltarThread::Run()
{
	// ·Îµù
	CSceneManager::GetInst()->CreateNextScene(false);
	CBalrogAltar* BalrogAltar = CSceneManager::GetInst()->CreateSceneModeEmpty<CBalrogAltar>(false);

	BalrogAltar->SetLoadingFunction<CBalrogAltarThread>(this, &CBalrogAltarThread::AddMessage);

	BalrogAltar->Init();

	AddMessage(true, 1.f);
}
