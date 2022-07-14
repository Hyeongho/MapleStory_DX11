#include "EditorMenu.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "Engine.h"
#include "PathManager.h"
#include "../EditorManager.h"
#include "../Object/SpriteEditObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"
#include "Component/TileMapComponent.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "../Object/DragObject.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"
#include "ObjectHierarchy.h"
#include "IMGUIManager.h"
#include "../Object/Player2D.h"

CEditorMenu::CEditorMenu()
{
}

CEditorMenu::~CEditorMenu()
{
}

bool CEditorMenu::Init()
{
	CIMGUIWindow::Init();

	m_ObjectCombo = AddWidget<CIMGUIComboBox>("ObjectCombo", 100.f, 30.f);

	m_ObjectCombo->SetHideName(true);
	m_ObjectCombo->AddItem("GameObject");
	m_ObjectCombo->AddItem("Player");

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectNameInput = AddWidget<CIMGUITextInput>("ObjectName", 100.f, 30.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ObjectCreateButton = AddWidget<CIMGUIButton>("CreateObject", 100.f, 30.f);

	m_ObjectCreateButton->SetClickCallback(this, &CEditorMenu::ObjectCreateButton);

	// Component
	m_ComponentCombo = AddWidget<CIMGUIComboBox>("ComponentCombo", 100.f, 30.f);

	m_ComponentCombo->SetHideName(true);
	m_ComponentCombo->AddItem("SpriteComponent");
	m_ComponentCombo->AddItem("StaticMeshComponent");
	m_ComponentCombo->AddItem("ColliderBox2DComponent");
	m_ComponentCombo->AddItem("ColliderCircleComponent");
	m_ComponentCombo->AddItem("ColliderPixelComponent");
	m_ComponentCombo->AddItem("CmaeraComponent");
	m_ComponentCombo->AddItem("WidgetComponent");
	m_ComponentCombo->AddItem("TileMapComponent");

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ComponentNameInput = AddWidget<CIMGUITextInput>("ComponentName", 100.f, 30.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ComponentCreateButton = AddWidget<CIMGUIButton>("CreateComponent", 100.f, 30.f);

	m_ComponentCreateButton->SetClickCallback(this, &CEditorMenu::ComponentCreateButton);

	CIMGUIButton* SaveSceneButton = AddWidget<CIMGUIButton>("SaveSceneButton", 100.f, 30.f);

	SaveSceneButton->SetClickCallback(this, &CEditorMenu::SaveScene);

	CIMGUIButton* LoadSceneButton = AddWidget<CIMGUIButton>("LoadSceneButton", 100.f, 30.f);

	LoadSceneButton->SetClickCallback(this, &CEditorMenu::LoadScene);

	CIMGUIButton* PlayButton = AddWidget<CIMGUIButton>("Play", 50.f, 50.f);

	PlayButton->SetClickCallback(this, &CEditorMenu::GamePlay);

	return true;
}

void CEditorMenu::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CEditorMenu::ObjectCreateButton()
{
	// 오브젝트 생성.
	int	SelectIndex = m_ObjectCombo->GetSelectIndex();
	if (SelectIndex == -1)
	{
		return;
	}

	switch ((CreateObject_Type)SelectIndex)
	{
	case CreateObject_Type::GameObject:
		CSceneManager::GetInst()->GetScene()->CreateGameObject<CGameObject>(m_ObjectNameInput->GetTextMultibyte());
		break;
	case CreateObject_Type::Player:
		CSceneManager::GetInst()->GetScene()->CreateGameObject<CPlayer2D>(m_ObjectNameInput->GetTextMultibyte());
		break;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (Hierarchy)
	{
		Hierarchy->AddObjectList(m_ObjectNameInput->GetTextMultibyte());
	}
}

void CEditorMenu::ComponentCreateButton()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	CGameObject* Obj = nullptr;

	if (Hierarchy)
	{
		CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

		if (ObjList->GetSelectIndex() == -1)
		{
			return;
		}

		Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());
	}

	if (!Obj)
	{
		return;
	}

	// 오브젝트 생성.
	int	SelectIndex = m_ComponentCombo->GetSelectIndex();
	if (SelectIndex == -1)
	{
		return;
	}

	switch ((SceneComponent_Type)SelectIndex)
	{
	case SceneComponent_Type::Sprite:
		if (Obj->GetRootComponent())
		{
			Obj->GetRootComponent()->AddChild(Obj->CreateComponent<CSpriteComponent>(m_ComponentNameInput->GetTextMultibyte()));

			break;
		}

		Obj->CreateComponent<CSpriteComponent>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::StaticMesh:
		if (Obj->GetRootComponent())
		{
			Obj->GetRootComponent()->AddChild(Obj->CreateComponent<CStaticMeshComponent>(m_ComponentNameInput->GetTextMultibyte()));

			break;
		}

		Obj->CreateComponent<CStaticMeshComponent>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::ColliderBox2D:
		if (Obj->GetRootComponent())
		{
			Obj->GetRootComponent()->AddChild(Obj->CreateComponent<CColliderBox2D>(m_ComponentNameInput->GetTextMultibyte()));

			break;
		}

		Obj->CreateComponent<CColliderBox2D>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::ColliderCircle:
		if (Obj->GetRootComponent())
		{
			Obj->GetRootComponent()->AddChild(Obj->CreateComponent<CColliderCircle>(m_ComponentNameInput->GetTextMultibyte()));

			break;
		}

		Obj->CreateComponent<CColliderCircle>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::ColliderPixel:
		if (Obj->GetRootComponent())
		{
			Obj->GetRootComponent()->AddChild(Obj->CreateComponent<CColliderPixel>(m_ComponentNameInput->GetTextMultibyte()));

			break;
		}

		Obj->CreateComponent<CColliderPixel>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::Camera:
		if (Obj->GetRootComponent())
		{
			Obj->GetRootComponent()->AddChild(Obj->CreateComponent<CCameraComponent>(m_ComponentNameInput->GetTextMultibyte()));

			break;
		}

		Obj->CreateComponent<CCameraComponent>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::Widget:
		if (Obj->GetRootComponent())
		{
			Obj->GetRootComponent()->AddChild(Obj->CreateComponent<CWidgetComponent>(m_ComponentNameInput->GetTextMultibyte()));

			break;
		}

		Obj->CreateComponent<CWidgetComponent>(m_ComponentNameInput->GetTextMultibyte());
		break;
	case SceneComponent_Type::TileMap:
	{
		CTileMapComponent* TileMap = Obj->CreateComponent<CTileMapComponent>(m_ComponentNameInput->GetTextMultibyte());

		CMaterial* Material = CSceneManager::GetInst()->GetScene()->GetResource()->FindMaterial("TileMap");

		TileMap->SetTileMaterial(Material);

		CEditorManager::GetInst()->SetEditMode(EditMode::TileMap);
	}
	break;
	}

	if (Hierarchy)
	{
		CIMGUIListBox* ComponentList = Hierarchy->GetComponentList();

		ComponentList->AddItem(m_ComponentNameInput->GetTextMultibyte());
	}
}

void CEditorMenu::SaveScene()
{
	TCHAR FilePath[MAX_PATH] = {};

	OPENFILENAME OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0Scene File\0*.scn");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		char ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CSceneManager::GetInst()->GetScene()->SaveFullPath(ConvertFullPath);
	}
}

void CEditorMenu::LoadScene()
{
	TCHAR FilePath[MAX_PATH] = {};

	OPENFILENAME OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0Scene File\0*.scn");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(SCENE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		char ConvertFullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, ConvertFullPath, Length, 0, 0);

		CSceneManager::GetInst()->GetScene()->LoadFullPath(ConvertFullPath);
	}
}

void CEditorMenu::GamePlay()
{
	if (!CEngine::GetInst()->IsPlay())
	{
		CEngine::GetInst()->SetPlay(true);
	}

	else
	{
		CEngine::GetInst()->SetPlay(false);
	}
}
