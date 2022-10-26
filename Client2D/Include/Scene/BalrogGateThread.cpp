#include "BalrogGateThread.h"
#include "BalrogGate.h"
#include "Scene/SceneManager.h"

CBalrogGateThread::CBalrogGateThread()
{
}

CBalrogGateThread::~CBalrogGateThread()
{
}

bool CBalrogGateThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CBalrogGateThread::Run()
{
	// ·Îµù
	CSceneManager::GetInst()->CreateNextScene(false);
	CBalrogGate* BalrogGate = CSceneManager::GetInst()->CreateSceneModeEmpty<CBalrogGate>(false);

	BalrogGate->SetLoadingFunction<CBalrogGateThread>(this, &CBalrogGateThread::AddMessage);

	BalrogGate->Init();

	AddMessage(true, 1.f);
}
