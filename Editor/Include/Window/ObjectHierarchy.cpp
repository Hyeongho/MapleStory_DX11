#include "ObjectHierarchy.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUIManager.h"
#include "Engine.h"
#include "PathManager.h"
#include "../EditorManager.h"
#include "../Object/SpriteEditObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "../Object/DragObject.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"
#include "ColliderBox2DWindow.h"
#include "Component/ColliderBox2D.h"
#include "TileMapWindow.h"

CObjectHierarchy::CObjectHierarchy()
{
}

CObjectHierarchy::~CObjectHierarchy()
{
}

void CObjectHierarchy::AddObjectList(const char* Name)
{
	m_ObjectListWidget->AddItem(Name);
}

bool CObjectHierarchy::Init()
{
	CIMGUIWindow::Init();

	m_ObjectListWidget = AddWidget<CIMGUIListBox>("ObjectList", 300.f, 500.f);

	m_ObjectListWidget->SetHideName(true);
	m_ObjectListWidget->SetPageItemCount(15);
	m_ObjectListWidget->SetSelectCallback(this, &CObjectHierarchy::SelectObject);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_ComponentListWidget = AddWidget<CIMGUIListBox>("ComponentList", 300.f, 500.f);

	m_ComponentListWidget->SetHideName(true);
	m_ComponentListWidget->SetPageItemCount(15);
	m_ComponentListWidget->SetSelectCallback(this, &CObjectHierarchy::SelectComponent);

	return true;
}

void CObjectHierarchy::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CObjectHierarchy::SelectObject(int Index, const char* Item)
{
	CGameObject* Object = CSceneManager::GetInst()->GetScene()->FindObject(Item);

	if (!Object)
	{
		return;
	}

	if (m_PrevObject)
	{
		if (m_ComponentListWidget->GetSelect())
		{
			m_ComponentListWidget->SetSelect(false);
			m_ComponentListWidget->SetSelectIndex(-1);
		}
	}

	m_SelectObject = Object;

	std::vector<FindComponentName> vecNames;

	Object->GetAllSceneComponentsName(vecNames);

	m_ComponentListWidget->Clear();

	size_t Size = vecNames.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_ComponentListWidget->AddItem(vecNames[i].Name);
	}

	m_PrevObject = Object;
}

void CObjectHierarchy::SelectComponent(int Index, const char* Item)
{
	if (!m_SelectObject)
	{
		return;
	}

	// 선택된 컴포넌트를 저장해둔다.
	m_SelectComponent = (CSceneComponent*)m_SelectObject->FindComponent(Item);

	CColliderBox2DWindow* ColliderBox2DWindow = (CColliderBox2DWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ColliderBox2DWindow");

	if (m_SelectComponent->CheckType<CColliderBox2D>())
	{
		if (ColliderBox2DWindow)
		{
			ColliderBox2DWindow->Open();
		}
	}

	else
	{
		ColliderBox2DWindow->Close();
	}

	CTileMapWindow* TileMapWindow = (CTileMapWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("TileMapWindow");

	if (TileMapWindow)
	{
		if (m_SelectComponent->CheckType<CTileMapComponent>())
		{
			TileMapWindow->SetTileMap((CTileMapComponent*)m_SelectComponent.Get());
		}

		else
		{
			TileMapWindow->SetTileMap(nullptr);
		}
	}
}
