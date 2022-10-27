#include "ClientSceneManager.h"
#include "Object/PlayerManager.h"
#include "Scene/SceneManager.h"
#include "Widget/Fade.h"
#include "ClientManager.h"
#include "Scene/LoadingSeolHui.h"
#include "Scene/LoadingEToTemple.h"
#include "Scene/LoadingAnotherDoor.h"
#include "Scene/LoadingBalrogGate.h"

DEFINITION_SINGLE(CClientSceneManager)

CClientSceneManager::CClientSceneManager()
{
}

CClientSceneManager::~CClientSceneManager()
{

}

bool CClientSceneManager::Init()
{
	return true;
}

void CClientSceneManager::ChangeScene()
{
	if (CSceneManager::GetInst()->GetNextScene())
	{
		return;
	}

	CFade* Fade = (CFade*)CSceneManager::GetInst()->GetScene()->GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

	if (Fade)
	{
		std::string CurrentScene = CPlayerManager::GetInst()->GetCurrnetScene();

		if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_End)
		{
			if (CurrentScene == "MainScene")
			{
				CSceneManager::GetInst()->CreateNextScene();
				CSceneManager::GetInst()->CreateSceneMode<CLoadingSeolHui>(false);
			}

			else if (CurrentScene == "AnotherDoor")
			{
				CSceneManager::GetInst()->CreateNextScene();
				CSceneManager::GetInst()->CreateSceneMode<CLoadingEToTemple>(false);
			}

			else if (CurrentScene == "EntranceToTemple")
			{
				CSceneManager::GetInst()->CreateNextScene();
				CSceneManager::GetInst()->CreateSceneMode<CLoadingBalrogGate>(false);
			}
		}
	}
}
