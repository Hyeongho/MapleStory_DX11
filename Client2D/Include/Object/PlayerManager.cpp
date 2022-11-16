#include "PlayerManager.h"
#include "../Widget/Fade.h"
#include "Scene/Scene.h"
#include "Scene/Scenemanager.h"
#include "../ClientManager.h"
#include "Scene/SceneResource.h"

DEFINITION_SINGLE(CPlayerManager)

CPlayerManager::CPlayerManager() : m_Gender(Gender::None), m_TagPotal(false), m_PlayerAttack(Player_Attack::Normal)
{
}

CPlayerManager::~CPlayerManager()
{
	
}

bool CPlayerManager::Init()
{
	CResourceManager::GetInst()->LoadSound("Skill", false, "PhantomBlow", "PhantomBlow/Use.mp3");
	CResourceManager::GetInst()->LoadSound("Skill", false, "BladeFury", "BladeFury/Use.mp3");

	return true;
}

void CPlayerManager::SceneChange()
{
	CFade* Fade = dynamic_cast<CFade*>(m_Scene->GetViewport()->FindWidgetWindow<CFade>("FadeWidget"));

	Fade->SetVisibility(true);

	CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_Start);
}

void CPlayerManager::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}