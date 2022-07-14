#include "DragObjWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUIRadio.h"
#include "IMGUICheckBox.h"
#include "IMGUISeparator.h"
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
#include "SpriteWindow.h"

CDragObjWindow::CDragObjWindow() : m_StartX(0.f), m_StartY(0.f), m_EndX(0.f), m_EndY(0.f), 
	m_PosX(0.f), m_PosY(0.f), m_ScaleX(0.f), m_ScaleY(0.f), m_PivotX(0.f), m_PivotY(0.f), m_Check(true)
{
}

CDragObjWindow::~CDragObjWindow()
{
}

bool CDragObjWindow::Init()
{
	CIMGUIWindow::Init();

	// DragObject StartPos
	CIMGUIText* StartX = AddWidget<CIMGUIText>("StartXText", 30.f, 100.f);

	StartX->SetText("StartX");
	StartX->SetColor(255, 255, 255);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_TextStartX = AddWidget<CIMGUIText>("StartX", 30.f, 100.f);
	std::string str_StartX = std::to_string(m_StartX);
	m_TextStartX->SetText(str_StartX.c_str());
	m_TextStartX->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(150.f);

	CIMGUIText* StartY = AddWidget<CIMGUIText>("StartYText", 30.f, 100.f);

	StartY->SetText("StartY");
	StartY->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextStartY = AddWidget<CIMGUIText>("StartY", 30.f, 100.f);
	std::string str_StartY = std::to_string(m_StartY);
	m_TextStartY->SetText(str_StartY.c_str());
	m_TextStartY->SetColor(255, 255, 255);

	// DragObject EndPos
	CIMGUIText* EndX = AddWidget<CIMGUIText>("EndXText", 30.f, 100.f);

	EndX->SetText("EndX");
	EndX->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextEndX = AddWidget<CIMGUIText>("EndX", 30.f, 100.f);
	std::string str_EndX = std::to_string(m_EndX);
	m_TextEndX->SetText(str_EndX.c_str());
	m_TextEndX->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(150.f);

	CIMGUIText* EndY = AddWidget<CIMGUIText>("EndYText", 30.f, 100.f);

	EndY->SetText("EndY");
	EndY->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextEndY = AddWidget<CIMGUIText>("EndY", 30.f, 100.f);
	std::string str_EndY = std::to_string(m_EndY);
	m_TextEndY->SetText(str_EndY.c_str());
	m_TextEndY->SetColor(255, 255, 255);

	// DragObj Pos
	m_TextPosX = AddWidget<CIMGUIText>("PosX", 30.f, 100.f);
	std::string str_PosX = std::to_string(m_PosX);
	m_TextPosX->SetText(str_PosX.c_str());
	m_TextPosX->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(150.f);

	m_TextPosY = AddWidget<CIMGUIText>("PosY", 30.f, 100.f);
	std::string str_PosY = std::to_string(m_PosY);
	m_TextPosY->SetText(str_PosY.c_str());
	m_TextPosY->SetColor(255, 255, 255);

	// DragObj Scale
	m_TextScaleX = AddWidget<CIMGUIText>("ScaleX", 30.f, 100.f);
	std::string str_ScaleX = std::to_string(m_ScaleX);
	m_TextScaleX->SetText(str_PosX.c_str());
	m_TextScaleX->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(150.f);

	m_TextScaleY = AddWidget<CIMGUIText>("ScaleY", 30.f, 100.f);
	std::string str_ScaleY = std::to_string(m_ScaleY);
	m_TextScaleY->SetText(str_PosY.c_str());
	m_TextScaleY->SetColor(255, 255, 255);

	// Transform 입력
	CIMGUILabel* Label = AddWidget<CIMGUILabel>("Transform", 100.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Label = AddWidget<CIMGUILabel>("StartPos", 80.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_StartXInput = AddWidget<CIMGUITextInput>("StartXInput", 60.f, 60.f);
	m_StartXInput->SetHideName(true);
	m_StartXInput->SetTextType(ImGuiText_Type::Float);
	m_StartXInput->SetCallback(this, &CDragObjWindow::StartXCallBack);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_StartYInput = AddWidget<CIMGUITextInput>("StartYInput", 60.f, 30.f);
	m_StartYInput->SetHideName(true);
	m_StartYInput->SetTextType(ImGuiText_Type::Float);
	m_StartYInput->SetCallback(this, &CDragObjWindow::StartYCallBack);

	Label = AddWidget<CIMGUILabel>("EndPos", 80.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_EndXInput = AddWidget<CIMGUITextInput>("EndXInput", 60.f, 60.f);
	m_EndXInput->SetHideName(true);
	m_EndXInput->SetTextType(ImGuiText_Type::Float);
	m_EndXInput->SetCallback(this, &CDragObjWindow::EndXCallBack);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_EndYInput = AddWidget<CIMGUITextInput>("EndYInput", 60.f, 30.f);
	m_EndYInput->SetHideName(true);
	m_EndYInput->SetTextType(ImGuiText_Type::Float);
	m_EndYInput->SetCallback(this, &CDragObjWindow::EndYCallBack);

	// Pos 설정
	Label = AddWidget<CIMGUILabel>("Pos", 80.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosXInput = AddWidget<CIMGUITextInput>("PosX", 60.f, 30.f);
	m_PosXInput->SetHideName(true);
	m_PosXInput->SetTextType(ImGuiText_Type::Float);
	m_PosXInput->SetCallback(this, &CDragObjWindow::PosXCallBack);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosYInput = AddWidget<CIMGUITextInput>("PosY", 60.f, 30.f);
	m_PosYInput->SetHideName(true);
	m_PosYInput->SetTextType(ImGuiText_Type::Float);
	m_PosYInput->SetCallback(this, &CDragObjWindow::PosYCallBack);

	// Scale 설정
	Label = AddWidget<CIMGUILabel>("Scale", 80.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ScaleXInput = AddWidget<CIMGUITextInput>("ScaleX", 60.f, 30.f);
	m_ScaleXInput->SetHideName(true);
	m_ScaleXInput->SetTextType(ImGuiText_Type::Float);
	m_ScaleXInput->SetCallback(this, &CDragObjWindow::ScaleXCallBack);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_ScaleYInput = AddWidget<CIMGUITextInput>("ScaleY", 60.f, 30.f);
	m_ScaleYInput->SetHideName(true);
	m_ScaleYInput->SetTextType(ImGuiText_Type::Float);
	m_ScaleYInput->SetCallback(this, &CDragObjWindow::ScaleYCallBack);

	// Pivot 설정
	Label = AddWidget<CIMGUILabel>("Pivot", 80.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PivotXInput = AddWidget<CIMGUITextInput>("PivotX", 60.f, 30.f);
	m_PivotXInput->SetHideName(true);
	m_PivotXInput->SetTextType(ImGuiText_Type::Float);
	m_PivotXInput->SetCallback(this, &CDragObjWindow::PivotXCallBack);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PivotYInput = AddWidget<CIMGUITextInput>("PivotY", 60.f, 30.f);
	m_PivotYInput->SetHideName(true);
	m_PivotYInput->SetTextType(ImGuiText_Type::Float);
	m_PivotYInput->SetCallback(this, &CDragObjWindow::PivotYCallBack);

	// 드래그
	m_CheckBox = AddWidget<CIMGUICheckBox>("IsDrag", 60.f, 30.f);
	m_CheckBox->SetCheck(m_Check);
	m_CheckBox->SetCallback(this, &CDragObjWindow::CheckCallBack);

	return true;
}

void CDragObjWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	Print();
}

void CDragObjWindow::Print()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	m_StartX = DragObj->GetStartPos().x;
	m_StartY = DragObj->GetStartPos().y;

	m_EndX = DragObj->GetEndPos().x;
	m_EndY = DragObj->GetEndPos().y;

	m_PosX = DragObj->GetWorldPos().x;
	m_PosY = DragObj->GetWorldPos().y;

	m_ScaleX = DragObj->GetWorldScale().x;
	m_ScaleY = DragObj->GetWorldScale().y;

	std::string StartX = std::to_string(m_StartX);
	std::string StartY = std::to_string(m_StartY);

	std::string EndX = std::to_string(m_EndX);
	std::string EndY = std::to_string(m_EndY);

	std::string PosX = std::to_string(m_PosX);
	std::string PosY = std::to_string(m_PosY);
	
	std::string ScaleX = std::to_string(m_ScaleX);
	std::string ScaleY = std::to_string(m_ScaleY);

	m_TextStartX->SetText(StartX.c_str());
	m_TextStartY->SetText(StartY.c_str());

	m_TextEndX->SetText(EndX.c_str());
	m_TextEndY->SetText(EndY.c_str());

	m_TextPosX->SetText(PosX.c_str());
	m_TextPosY->SetText(PosY.c_str());

	m_TextScaleX->SetText(ScaleX.c_str());
	m_TextScaleY->SetText(ScaleY.c_str());
}

void CDragObjWindow::StartXCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector2	Pos = DragObj->GetStartPos();

	Pos.x = m_StartXInput->GetValueFloat();

	DragObj->SetStartPos(Pos);
}

void CDragObjWindow::StartYCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector2	Pos = DragObj->GetStartPos();

	Pos.y = m_StartYInput->GetValueFloat();

	DragObj->SetStartPos(Pos);
}

void CDragObjWindow::EndXCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector2	Pos = DragObj->GetEndPos();

	Pos.x = m_EndXInput->GetValueFloat();

	DragObj->SetEndPos(Pos);
}

void CDragObjWindow::EndYCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector2	Pos = DragObj->GetEndPos();

	Pos.y = m_EndYInput->GetValueFloat();

	DragObj->SetEndPos(Pos);
}

void CDragObjWindow::PosXCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector3 Pos = DragObj->GetWorldPos();

	Pos.x = m_PosXInput->GetValueFloat();

	DragObj->SetWorldPos(Pos);
}

void CDragObjWindow::PosYCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector3 Pos = DragObj->GetWorldPos();

	Pos.y = m_PosYInput->GetValueFloat();

	DragObj->SetWorldPos(Pos);
}

void CDragObjWindow::ScaleXCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector3 Scale = DragObj->GetWorldScale();

	Scale.x = m_ScaleXInput->GetValueFloat();

	DragObj->SetWorldScale(Scale);
}

void CDragObjWindow::ScaleYCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector3 Scale = DragObj->GetWorldScale();

	Scale.y = m_ScaleYInput->GetValueFloat();

	DragObj->SetWorldScale(Scale);
}

void CDragObjWindow::PivotXCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector3 Pivot = DragObj->GetPivot();

	Pivot.x = m_PivotXInput->GetValueFloat();

	DragObj->SetPivot(Pivot);
}

void CDragObjWindow::PivotYCallBack()
{
	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}

	Vector3 Pivot = DragObj->GetPivot();

	Pivot.y = m_PivotYInput->GetValueFloat();

	DragObj->SetPivot(Pivot);
}

void CDragObjWindow::CheckCallBack(bool Check)
{
	m_Check = Check;

	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	if (!DragObj)
	{
		return;
	}

	CGameObject* Obj = nullptr;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject("DragObject");

	if (!Obj)
	{
		return;
	}
}

