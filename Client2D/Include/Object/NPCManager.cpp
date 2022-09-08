#include "NPCManager.h"
#include "../Widget/TalkWidget.h"
#include "Scene/Scene.h"
#include "Input.h"

CNPCManager::CNPCManager() : m_Click(false), m_ID(0), m_Action(false), m_NPCName(nullptr)
{
}

CNPCManager::CNPCManager(const CNPCManager& obj) : CGameObject(obj)
{
}

CNPCManager::~CNPCManager()
{
}

void CNPCManager::Talk(int ID)
{
	CTalkWidget* TalkWidget = m_Scene->GetViewport()->FindWidgetWindow<CTalkWidget>("TalkWidget");

	if (m_ID == 0)
	{
		TalkWidget->SetVisibility(false);

		return;
	}

	else
	{
		if (!TalkWidget->GetVisibility())
		{
			TalkWidget->SetVisibility(true);
		}
	}

	m_Action = true;

	TalkWidget->SetTalk(m_ID, m_NPCName);
}

void CNPCManager::Start()
{
	CGameObject::Start();
}

bool CNPCManager::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	return true;
}

void CNPCManager::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (CClientManager::GetInst()->GetFade())
	{
		return;
	}

	CTalkWidget* TalkWidget = m_Scene->GetViewport()->FindWidgetWindow<CTalkWidget>("TalkWidget");

	if (m_Click && CInput::GetInst()->GetMouseLButtonClick())
	{
		if (!TalkWidget->GetVisibility())
		{
			TalkWidget->SetVisibility(true);
		}

		Talk(m_ID);
	}
}

void CNPCManager::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (CClientManager::GetInst()->GetFade())
	{
		return;
	}
}

CNPCManager* CNPCManager::Clone()
{
	return new CNPCManager(*this);
}
