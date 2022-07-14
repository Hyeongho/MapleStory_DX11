#include "DetailWindow.h"
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
#include "Resource/Animation/AnimationSequence2D.h"
#include "../Object/DragObject.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"
#include "ObjectHierarchy.h"
#include "IMGUIManager.h"

CDetailWindow::CDetailWindow()
{
}

CDetailWindow::~CDetailWindow()
{
}

bool CDetailWindow::Init()
{
	CIMGUIWindow::Init();

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("Transform", 100.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Label = AddWidget<CIMGUILabel>("Position", 60.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);	

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosX = AddWidget<CIMGUITextInput>("PositionX", 60.f, 30.f);
	m_PosX->SetHideName(true);
	m_PosX->SetTextType(ImGuiText_Type::Float);
	m_PosX->SetCallback(this, &CDetailWindow::PositionXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosY = AddWidget<CIMGUITextInput>("PositionY", 60.f, 30.f);
	m_PosY->SetHideName(true);
	m_PosY->SetTextType(ImGuiText_Type::Float);
	m_PosY->SetCallback(this, &CDetailWindow::PositionYCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosZ = AddWidget<CIMGUITextInput>("PositionZ", 60.f, 30.f);
	m_PosZ->SetHideName(true);
	m_PosZ->SetTextType(ImGuiText_Type::Float);
	m_PosZ->SetCallback(this, &CDetailWindow::PositionZCallback);

	Label = AddWidget<CIMGUILabel>("Scale", 60.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ScaleX = AddWidget<CIMGUITextInput>("ScaleX", 60.f, 30.f);
	m_ScaleX->SetHideName(true);
	m_ScaleX->SetTextType(ImGuiText_Type::Float);
	m_ScaleX->SetCallback(this, &CDetailWindow::ScaleXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ScaleY = AddWidget<CIMGUITextInput>("ScaleY", 60.f, 30.f);
	m_ScaleY->SetHideName(true);
	m_ScaleY->SetTextType(ImGuiText_Type::Float);
	m_ScaleY->SetCallback(this, &CDetailWindow::ScaleYCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ScaleZ = AddWidget<CIMGUITextInput>("ScaleZ", 60.f, 30.f);
	m_ScaleZ->SetHideName(true);
	m_ScaleZ->SetTextType(ImGuiText_Type::Float);
	m_ScaleZ->SetCallback(this, &CDetailWindow::ScaleZCallback);

	Label = AddWidget<CIMGUILabel>("Location", 60.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_RotX = AddWidget<CIMGUITextInput>("LocationX", 60.f, 30.f);
	m_RotX->SetHideName(true);
	m_RotX->SetTextType(ImGuiText_Type::Float);
	m_RotX->SetCallback(this, &CDetailWindow::LocationXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_RotY = AddWidget<CIMGUITextInput>("LocationY", 60.f, 30.f);
	m_RotY->SetHideName(true);
	m_RotY->SetTextType(ImGuiText_Type::Float);
	m_RotY->SetCallback(this, &CDetailWindow::LocationYCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_RotZ = AddWidget<CIMGUITextInput>("LocationZ", 60.f, 30.f);
	m_RotZ->SetHideName(true);
	m_RotZ->SetTextType(ImGuiText_Type::Float);
	m_RotZ->SetCallback(this, &CDetailWindow::LocationZCallback);

	Label = AddWidget<CIMGUILabel>("Pivot", 60.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PivotX = AddWidget<CIMGUITextInput>("PivotX", 60.f, 30.f);
	m_PivotX->SetHideName(true);
	m_PivotX->SetTextType(ImGuiText_Type::Float);
	m_PivotX->SetCallback(this, &CDetailWindow::PivotXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PivotY = AddWidget<CIMGUITextInput>("PivotY", 60.f, 30.f);
	m_PivotY->SetHideName(true);
	m_PivotY->SetTextType(ImGuiText_Type::Float);
	m_PivotY->SetCallback(this, &CDetailWindow::PivotYCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PivotZ = AddWidget<CIMGUITextInput>("PivotZ", 60.f, 30.f);
	m_PivotZ->SetHideName(true);
	m_PivotZ->SetTextType(ImGuiText_Type::Float);
	m_PivotZ->SetCallback(this, &CDetailWindow::PivotZCallback);

	return true;
}

void CDetailWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CDetailWindow::PositionXCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3	Pos = Obj->GetRootComponent()->GetWorldPos();

	Pos.x = m_PosX->GetValueFloat();

	Obj->GetRootComponent()->SetWorldPos(Pos);
}

void CDetailWindow::PositionYCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3	Pos = Obj->GetRootComponent()->GetWorldPos();

	Pos.y = m_PosY->GetValueFloat();

	Obj->GetRootComponent()->SetWorldPos(Pos);
}

void CDetailWindow::PositionZCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3	Pos = Obj->GetRootComponent()->GetWorldPos();

	Pos.z = m_PosZ->GetValueFloat();

	Obj->GetRootComponent()->SetWorldPos(Pos);
}

void CDetailWindow::ScaleXCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3	Scale = Obj->GetRootComponent()->GetWorldScale();

	Scale.x = m_ScaleX->GetValueFloat();

	Obj->GetRootComponent()->SetWorldScale(Scale);
}

void CDetailWindow::ScaleYCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3	Scale = Obj->GetRootComponent()->GetWorldScale();

	Scale.y = m_ScaleY->GetValueFloat();

	Obj->GetRootComponent()->SetWorldScale(Scale);
}

void CDetailWindow::ScaleZCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3	Scale = Obj->GetRootComponent()->GetWorldScale();

	Scale.z = m_ScaleZ->GetValueFloat();

	Obj->GetRootComponent()->SetWorldScale(Scale);
}

void CDetailWindow::LocationXCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	float Rotation = Obj->GetRootComponent()->GetWorldRot().x;

	Rotation = m_RotX->GetValueFloat();

	Obj->GetRootComponent()->SetWorldRotationX(Rotation);
}

void CDetailWindow::LocationYCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	float Rotation = Obj->GetRootComponent()->GetWorldRot().y;

	Rotation = m_RotY->GetValueFloat();

	Obj->GetRootComponent()->SetWorldRotationY(Rotation);
}


void CDetailWindow::LocationZCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	float Rotation = Obj->GetRootComponent()->GetWorldRot().z;

	Rotation = m_RotZ->GetValueFloat();

	Obj->GetRootComponent()->SetWorldRotationZ(Rotation);
}

void CDetailWindow::PivotXCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3 Pivot = Obj->GetRootComponent()->GetPivot();

	Pivot.x = m_PivotX->GetValueFloat();

	Obj->GetRootComponent()->SetPivot(Pivot);
}

void CDetailWindow::PivotYCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3 Pivot = Obj->GetRootComponent()->GetPivot();

	Pivot.y = m_PivotY->GetValueFloat();

	Obj->GetRootComponent()->SetPivot(Pivot);
}

void CDetailWindow::PivotZCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
	{
		return;
	}

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
	{
		return;
	}

	Vector3 Pivot = Obj->GetRootComponent()->GetPivot();

	Pivot.z = m_PivotZ->GetValueFloat();

	Obj->GetRootComponent()->SetPivot(Pivot);
}
