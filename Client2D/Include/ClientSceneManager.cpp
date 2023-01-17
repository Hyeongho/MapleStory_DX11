#include "ClientSceneManager.h"
#include "Object/PlayerManager.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
#include "Widget/Fade.h"
#include "ClientManager.h"
#include "Scene/LoadingSeolHui.h"
#include "Scene/LoadingEToTemple.h"
#include "Scene/LoadingAnotherDoor.h"
#include "Scene/LoadingBalrogGate.h"
#include "Scene/LoadingStartScene.h"
#include "Object/Player2D.h"

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

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CFade* Fade = Scene->GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

	if (Fade)
	{
		std::string CurrentScene = CPlayerManager::GetInst()->GetCurrnetScene();

		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(Scene->GetPlayerObject());

		if (Player)
		{
			if (Player->GetPlayerState() == EPlayer_State::Die)
			{
				if (CurrentScene == "EntranceToTemple")
				{
					CSceneManager::GetInst()->CreateNextScene();
					CSceneManager::GetInst()->CreateSceneMode<CLoadingAnotherDoor>(false);

					return;
				}

				else if (CurrentScene == "BalrogAltar")
				{
					CSceneManager::GetInst()->CreateNextScene();
					CSceneManager::GetInst()->CreateSceneMode<CLoadingBalrogGate>(false);

					return;
				}
			}
		}

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

			else if (CurrentScene == "BalrogAltar")
			{
				CSceneManager::GetInst()->CreateNextScene();
				CSceneManager::GetInst()->CreateSceneMode<CLoadingStartScene>(false);
			}
		}
	}
}
