#include "EditorManager.h"
#include "Engine.h"
#include "resource.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/DefaultScene.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"
#include "Input.h"
#include "IMGUIManager.h"
#include "Window/SpriteWindow.h"
#include "Window/DetailWindow.h"
#include "Window/EditorMenu.h"
#include "Window/ObjectHierarchy.h"
#include "Window/DragObjWindow.h"
#include "Window/TileMapWindow.h"
#include "Window/ColliderBox2DWindow.h"
#include "Object/DragObject.h"
#include "Render/RenderManager.h"
#include "Object/SpriteEditObject.h"
#include "Component/SpriteComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"
#include "Animation/AnimationSequence2DInstance.h"

DEFINITION_SINGLE(CEditorManager)

CEditorManager::CEditorManager() : m_EditMode(EditMode::Scene), m_DragObj(nullptr), m_CameraMoveSpeed(1000.f)
{
}

CEditorManager::~CEditorManager()
{
	CEngine::DestroyInst();
}

void CEditorManager::SetEditMode(EditMode Mode)
{
	m_EditMode = Mode;

	switch (m_EditMode)
	{
	case EditMode::Scene:
		break;
	case EditMode::Sprite:
		if (m_DragObj)
		{
			m_DragObj->Destroy();
		}

		m_DragObj = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDragObject>("DragObject");
		m_DragObj->SetWorldScale(0.f, 0.f, 1.f);
		break;
	case EditMode::TileMap:
		if (m_DragObj)
		{
			m_DragObj->Destroy();
			m_DragObj = nullptr;
		}
		break;
	}

	if (m_EditMode == EditMode::Sprite)
	{
	}
}

bool CEditorManager::Init(HINSTANCE hInst)
{
	if (!CEngine::GetInst()->Init(hInst, TEXT("Editor"), 1366, 768, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	CSceneManager::GetInst()->SetCreateSceneModeFunction<CEditorManager>(this, &CEditorManager::CreateSceneMode);
	CSceneManager::GetInst()->SetCreateObjectFunction<CEditorManager>(this, &CEditorManager::CreateObject);
	CSceneManager::GetInst()->SetCreateComponentFunction<CEditorManager>(this, &CEditorManager::CreateComponent);
	CSceneManager::GetInst()->SetCreateAnimInstanceFunction<CEditorManager>(this, &CEditorManager::CreateAnimInstance);

	CSceneManager::GetInst()->SetProjectType(Project_Type::Editor);

	// IMGUI로 에디터에서 사용할 윈도우를 만들어준다.
	m_SpriteWindow = CIMGUIManager::GetInst()->AddWindow<CSpriteWindow>("SpriteWindow");
	m_DetailWindow = CIMGUIManager::GetInst()->AddWindow<CDetailWindow>("DetailWindow");
	m_EditorMenu = CIMGUIManager::GetInst()->AddWindow<CEditorMenu>("EditorMenu");
	m_ObjectHierarchy = CIMGUIManager::GetInst()->AddWindow<CObjectHierarchy>("ObjectHierarchy");
	m_TileMapWindow = CIMGUIManager::GetInst()->AddWindow<CTileMapWindow>("TileMapWindow");
	m_DragObjWindow = CIMGUIManager::GetInst()->AddWindow<CDragObjWindow>("DragObjWindow");

	m_ColliderBox2DWindow = CIMGUIManager::GetInst()->AddWindow<CColliderBox2DWindow>("ColliderBox2DWindow");

	//m_EditorMenu->Open();
	m_ColliderBox2DWindow->Close();

	CRenderManager::GetInst()->CreateLayer("DragLayer", INT_MAX);

	CInput::GetInst()->CreateKey("MouseLButton", VK_LBUTTON);
	CInput::GetInst()->SetKeyCallback("MouseLButton", KeyState_Down, this, &CEditorManager::MouseLButtonDown);
	CInput::GetInst()->SetKeyCallback("MouseLButton", KeyState_Push, this, &CEditorManager::MouseLButtonPush);
	CInput::GetInst()->SetKeyCallback("MouseLButton", KeyState_Up, this, &CEditorManager::MouseLButtonUp);

	CInput::GetInst()->CreateKey("MouseRButton", VK_RBUTTON);
	CInput::GetInst()->SetKeyCallback("MouseRButton", KeyState_Down, this, &CEditorManager::MouseRButtonDown);
	CInput::GetInst()->SetKeyCallback("MouseRButton", KeyState_Push, this, &CEditorManager::MouseRButtonPush);
	CInput::GetInst()->SetKeyCallback("MouseRButton", KeyState_Up, this, &CEditorManager::MouseRButtonUp);

	CInput::GetInst()->CreateKey("Up", VK_UP);
	CInput::GetInst()->CreateKey("Down", VK_DOWN);
	CInput::GetInst()->CreateKey("Left", VK_LEFT);
	CInput::GetInst()->CreateKey("Right", VK_RIGHT);

	CInput::GetInst()->SetKeyCallback("Up", KeyState_Push, this, &CEditorManager::KeyboardUp);
	CInput::GetInst()->SetKeyCallback("Down", KeyState_Push, this, &CEditorManager::KeyboardDown);
	CInput::GetInst()->SetKeyCallback("Left", KeyState_Push, this, &CEditorManager::KeyboardLeft);
	CInput::GetInst()->SetKeyCallback("Right", KeyState_Push, this, &CEditorManager::KeyboardRight);

	return true;
}

void CEditorManager::CreateDefaultSceneMode()
{
	CSceneManager::GetInst()->CreateSceneMode<CDefaultScene>();
}

int CEditorManager::Run()
{
	return CEngine::GetInst()->Run();
}

void CEditorManager::MouseLButtonDown(float DeltaTime)
{
	if (!m_DragObjWindow->GetCheck())
	{
		return;
	}

	if (m_DragObj)
	{
		m_DragObj->SetStartPos(CInput::GetInst()->GetMousePos());
	}
}

void CEditorManager::MouseLButtonPush(float DeltaTime)
{
	m_MouseLPush = true;

	if (!m_DragObjWindow->GetCheck())
	{
		return;
	}

	if (m_DragObj)
	{
		m_DragObj->SetEndPos(CInput::GetInst()->GetMousePos());
	}
}

void CEditorManager::MouseLButtonUp(float DeltaTime)
{
	m_MouseLPush = false;
}

void CEditorManager::MouseRButtonDown(float DeltaTime)
{
}

void CEditorManager::MouseRButtonPush(float DeltaTime)
{
	m_MouseRPush = true;
}

void CEditorManager::MouseRButtonUp(float DeltaTime)
{
	m_MouseRPush = false;
}

void CEditorManager::KeyboardUp(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(0.f, 1.f, 0.f);
	}

	else
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPos(Vector3(0.f, m_CameraMoveSpeed * DeltaTime, 0.f));
	}
}

void CEditorManager::KeyboardDown(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(0.f, -1.f, 0.f);
	}

	else
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPos(Vector3(0.f, -m_CameraMoveSpeed * DeltaTime, 0.f));
	}
}

void CEditorManager::KeyboardLeft(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(-1.f, 0.f, 0.f);
	}

	else
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPos(Vector3(-m_CameraMoveSpeed * DeltaTime, 0.f, 0.f));
	}
}

void CEditorManager::KeyboardRight(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(1.f, 0.f, 0.f);
	}

	else
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPos(Vector3(m_CameraMoveSpeed * DeltaTime, 0.f, 0.f));
	}
}

void CEditorManager::CreateSceneMode(CScene* Scene, size_t Type)
{
	if (Type == typeid(CDefaultScene).hash_code())
	{
		Scene->LoadSceneMode<CDefaultScene>();
	}
}

CGameObject* CEditorManager::CreateObject(CScene* Scene, size_t Type)
{
	if (Type == typeid(CGameObject).hash_code())
	{
		CGameObject* Obj = Scene->LoadGameObject<CGameObject>();

		return Obj;
	}

	else if (Type == typeid(CDragObject).hash_code())
	{
		CDragObject* Obj = Scene->LoadGameObject<CDragObject>();

		return Obj;
	}

	else if (Type == typeid(CSpriteEditObject).hash_code())
	{
		CSpriteEditObject* Obj = Scene->LoadGameObject<CSpriteEditObject>();

		return Obj;
	}

	return nullptr;
}

CComponent* CEditorManager::CreateComponent(CGameObject* Obj, size_t Type)
{
	if (Type == typeid(CSceneComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSceneComponent>();

		return Component;
	}

	else if (Type == typeid(CSpriteComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSpriteComponent>();

		return Component;
	}

	else if (Type == typeid(CStaticMeshComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CStaticMeshComponent>();

		return Component;
	}

	else if (Type == typeid(CStaticMeshComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CStaticMeshComponent>();

		return Component;
	}

	else if (Type == typeid(CColliderBox2D).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CColliderBox2D>();

		return Component;
	}

	else if (Type == typeid(CColliderCircle).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CColliderCircle>();

		return Component;
	}

	else if (Type == typeid(CColliderPixel).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CColliderPixel>();

		return Component;
	}

	else if (Type == typeid(CCameraComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CCameraComponent>();

		return Component;
	}

	else if (Type == typeid(CWidgetComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CWidgetComponent>();

		return Component;
	}

	else if (Type == typeid(CTileMapComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CTileMapComponent>();

		return Component;
	}	

	return nullptr;
}

void CEditorManager::CreateAnimInstance(CSpriteComponent* Sprite, size_t Type)
{
	if (Type == typeid(CAnimationSequence2DInstance).hash_code())
	{
		Sprite->LoadAnimationInstance<CAnimationSequence2DInstance>();
	}
}
