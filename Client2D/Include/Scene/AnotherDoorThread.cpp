#include "AnotherDoorThread.h"
#include "AnotherDoor.h"
#include "Scene/SceneManager.h"

CAnotherDoorThread::CAnotherDoorThread()
{
}

CAnotherDoorThread::~CAnotherDoorThread()
{
}

bool CAnotherDoorThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CAnotherDoorThread::Run()
{
	// ·Îµù
	CSceneManager::GetInst()->CreateNextScene(false);
	CAnotherDoor* AnotherDoor = CSceneManager::GetInst()->CreateSceneModeEmpty<CAnotherDoor>(false);

	AnotherDoor->SetLoadingFunction<CAnotherDoorThread>(this, &CAnotherDoorThread::AddMessage);

	AnotherDoor->Init();

	AddMessage(true, 1.f);
}
