#include "EToTempleThread.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"
#include "EntranceToTemple.h"

CEToTempleThread::CEToTempleThread()
{
}

CEToTempleThread::~CEToTempleThread()
{
}

bool CEToTempleThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CEToTempleThread::Run()
{
	// ·Îµù
	CSceneManager::GetInst()->CreateNextScene(false);
	CEntranceToTemple* EntranceToTemple = CSceneManager::GetInst()->CreateSceneModeEmpty<CEntranceToTemple>(false);

	EntranceToTemple->SetLoadingFunction<CEToTempleThread>(this, &CEToTempleThread::AddMessage);

	EntranceToTemple->Init();

	AddMessage(true, 1.f);
}
