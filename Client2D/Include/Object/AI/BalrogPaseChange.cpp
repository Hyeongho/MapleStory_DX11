#include "BalrogPaseChange.h"
#include "../BalrogLeft.h"
#include "../BalrogRight.h"
#include "../Balrog.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Input.h"

CBalrogPaseChange::CBalrogPaseChange()
{
	
}

CBalrogPaseChange::~CBalrogPaseChange()
{
}

bool CBalrogPaseChange::Run()
{
	m_Balrog = (CBalrog*)CSceneManager::GetInst()->GetScene()->FindObject("Balrog");

	if (!m_Balrog)
	{
		return false;
	}

	OutputDebugStringA("Change");

	return true;
}
