#include "BalrogPaseChange.h"
#include "../BalrogLeft.h"
#include "../BalrogRight.h"
#include "../Balrog.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Input.h"

CBalrogPaseChange::CBalrogPaseChange() : m_Balrog(nullptr)
{
	
}

CBalrogPaseChange::~CBalrogPaseChange()
{
}

bool CBalrogPaseChange::Run()
{
	m_Balrog = dynamic_cast<CBalrog*>(CSceneManager::GetInst()->GetScene()->FindObject("Balrog"));

	if (!m_Balrog)
	{
		return false;
	}

	if (m_Balrog->GetBalrogLeft()->CheckDie() && m_Balrog->GetBalrogRight()->CheckDie())
	{
		OutputDebugStringA("Change");

		m_Balrog->SetBTRun(false);

		return true;
	}

	return true;
}
