#include "SceneManager.h"
#include "../Render/RenderManager.h"
#include "../Sync.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager() : m_Scene(nullptr), m_NextScene(nullptr)
{
	InitializeCriticalSection(&m_Crt);
}

CSceneManager::~CSceneManager()
{
	DeleteCriticalSection(&m_Crt);
	SAFE_DELETE(m_Scene);
	SAFE_DELETE(m_NextScene);
}

void CSceneManager::Start()
{
	m_Scene->Start();
}

bool CSceneManager::Init()
{
	m_Scene = new CScene;

	CRenderManager::GetInst()->SetObjectList(&m_Scene->m_ObjList);

	return true;
}

bool CSceneManager::Update(float DeltaTime)
{
	m_Scene->Update(DeltaTime);

	return ChangeScene();
}

bool CSceneManager::PostUpdate(float DeltaTime)
{
	m_Scene->PostUpdate(DeltaTime);

	return ChangeScene();
}

bool CSceneManager::ChangeScene()
{
	CSync sync(&m_Crt);

	if (m_NextScene)
	{
		if (m_NextScene->m_Change)
		{			
			SAFE_DELETE(m_Scene);

			m_Scene = m_NextScene;
			m_NextScene = nullptr;

			CRenderManager::GetInst()->SetObjectList(&m_Scene->m_ObjList);

			m_Scene->Start();

			return true;
		}
	}

	return false;
}

void CSceneManager::CreateNextScene(bool AutoChange)
{
	CSync sync(&m_Crt);

	SAFE_DELETE(m_NextScene);

	m_NextScene = new CScene;

	m_NextScene->SetAutoChange(AutoChange);
}

void CSceneManager::ChangeNextScene()
{
	CSync sync(&m_Crt);

	m_NextScene->SetAutoChange(true);
}
