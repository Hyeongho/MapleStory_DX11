#include "DataManager.h"
#include "Engine.h"
#include "resource.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/DefaultScene.h"
#include "IMGUIManager.h"
#include "Window/DataWindow.h"
#include "Window/DataWindowTable.h"
#include "Component/SpriteComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"
#include "Animation/AnimationSequence2DInstance.h"

DEFINITION_SINGLE(CDataManager)

CDataManager::CDataManager()
{
}

CDataManager::~CDataManager()
{
	CEngine::DestroyInst();
}

bool CDataManager::Init(HINSTANCE hInst)
{
	CEngine::GetInst()->SetPlay(false);

	if (!CEngine::GetInst()->Init(hInst, TEXT("Data"), 1366, 768, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	CSceneManager::GetInst()->SetProjectType(Project_Type::Data);

	m_DataWindow = CIMGUIManager::GetInst()->AddWindow<CDataWindow>("DataWindow");
	m_DataWindowTale = CIMGUIManager::GetInst()->AddWindow<CDataWindowTable>("DataWindowTable");

	return true;
}

void CDataManager::CreateDefaultSceneMode()
{
	CSceneManager::GetInst()->CreateSceneMode<CDefaultScene>();
}

int CDataManager::Run()
{
	return CEngine::GetInst()->Run();
}
