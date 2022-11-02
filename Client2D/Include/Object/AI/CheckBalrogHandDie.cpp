#include "CheckBalrogHandDie.h"
#include "../BalrogLeft.h"
#include "../BalrogRight.h"
#include "../Balrog.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Input.h"

CCheckBalrogHandDie::CCheckBalrogHandDie()
{
	m_Balrog = (CBalrog*)CSceneManager::GetInst()->GetScene()->FindObject("Balrog");
}

CCheckBalrogHandDie::~CCheckBalrogHandDie()
{
}

bool CCheckBalrogHandDie::Run()
{
	if (!m_Balrog)
	{
		return false;
	}

	if (m_Balrog->GetBalrogLeft()->CheckDie() && m_Balrog->GetBalrogRight()->CheckDie())
	{
		return true;
	}

	return false;
}
