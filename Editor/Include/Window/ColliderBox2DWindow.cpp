#include "ColliderBox2DWindow.h"
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
#include "Component/ColliderBox2D.h"

CColliderBox2DWindow::CColliderBox2DWindow() : m_Width(0.f), m_Height(0.f), m_Profile{}
{
}

CColliderBox2DWindow::~CColliderBox2DWindow()
{
}

bool CColliderBox2DWindow::Init()
{
	CIMGUIWindow::Init();

	// SetExtent
	CIMGUILabel* Label = AddWidget<CIMGUILabel>("Extent", 100.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	CIMGUIText* Text = AddWidget<CIMGUIText>("Width", 60.f, 30.f);

	Text->SetColor(0, 0, 255);
	Text->SetText("Width");
	Text->SetColor(255, 255, 255);

	CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");

	m_TextWidth = AddWidget<CIMGUIText>("TextWidth", 60.f, 30.f);

	m_TextWidth->SetColor(0, 0, 255);
	std::string str = std::to_string(m_Width);
	m_TextWidth->SetText(str.c_str());
	m_TextWidth->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputWidth = AddWidget<CIMGUITextInput>("Width", 60.f, 30.f);
	m_InputWidth->SetHideName(true);
	m_InputWidth->SetTextType(ImGuiText_Type::Float);
	m_InputWidth->SetCallback(this, &CColliderBox2DWindow::WidthCallback);

	Text = AddWidget<CIMGUIText>("Height", 60.f, 30.f);

	Text->SetColor(0, 0, 255);
	Text->SetText("Height");
	Text->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextHeight = AddWidget<CIMGUIText>("TextHeight", 60.f, 30.f);

	m_TextHeight->SetColor(0, 0, 255);
	str = std::to_string(m_Height);
	m_TextHeight->SetText(str.c_str());
	m_TextHeight->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputHeight = AddWidget<CIMGUITextInput>("Height", 60.f, 30.f);
	m_InputHeight->SetHideName(true);
	m_InputHeight->SetTextType(ImGuiText_Type::Float);
	m_InputHeight->SetCallback(this, &CColliderBox2DWindow::HeightCallback);

	//Set Pos
	Label = AddWidget<CIMGUILabel>("Position", 100.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Text = AddWidget<CIMGUIText>("PosX", 60.f, 30.f);

	Text->SetColor(0, 0, 255);
	Text->SetText("PosX");
	Text->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextPosX = AddWidget<CIMGUIText>("TextPosX", 60.f, 30.f);

	m_TextPosX->SetColor(0, 0, 255);
	str = std::to_string(m_PosX);
	m_TextPosX->SetText(str.c_str());
	m_TextPosX->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputPosX = AddWidget<CIMGUITextInput>("PosX", 60.f, 30.f);
	m_InputPosX->SetHideName(true);
	m_InputPosX->SetTextType(ImGuiText_Type::Float);
	m_InputPosX->SetCallback(this, &CColliderBox2DWindow::PosXCallback);

	Text = AddWidget<CIMGUIText>("PosY", 60.f, 30.f);

	Text->SetColor(0, 0, 255);
	Text->SetText("PosY");
	Text->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextPosY = AddWidget<CIMGUIText>("TextPosY", 60.f, 30.f);

	m_TextPosY->SetColor(0, 0, 255);
	str = std::to_string(m_PosY);
	m_TextPosY->SetText(str.c_str());
	m_TextPosY->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputPosY = AddWidget<CIMGUITextInput>("PosY", 60.f, 30.f);
	m_InputPosY->SetHideName(true);
	m_InputPosY->SetTextType(ImGuiText_Type::Float);
	m_InputPosY->SetCallback(this, &CColliderBox2DWindow::PosYCallback);

	//Set Pivot
	Label = AddWidget<CIMGUILabel>("Pivot", 100.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Text = AddWidget<CIMGUIText>("PivotX", 60.f, 30.f);

	Text->SetColor(0, 0, 255);
	Text->SetText("PivotX");
	Text->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextPivotX = AddWidget<CIMGUIText>("PivotX", 60.f, 30.f);

	m_TextPivotX->SetColor(0, 0, 255);
	str = std::to_string(m_PivotX);
	m_TextPivotX->SetText(str.c_str());
	m_TextPivotX->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputPivotX = AddWidget<CIMGUITextInput>("PivotX", 60.f, 30.f);
	m_InputPivotX->SetHideName(true);
	m_InputPivotX->SetTextType(ImGuiText_Type::Float);
	m_InputPivotX->SetCallback(this, &CColliderBox2DWindow::PivotXCallback);

	Text = AddWidget<CIMGUIText>("PivotY", 60.f, 30.f);

	Text->SetColor(0, 0, 255);
	Text->SetText("PivotY");
	Text->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextPivotY = AddWidget<CIMGUIText>("PivotY", 60.f, 30.f);

	m_TextPivotY->SetColor(0, 0, 255);
	str = std::to_string(m_PivotY);
	m_TextPivotY->SetText(str.c_str());
	m_TextPivotY->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputPivotY = AddWidget<CIMGUITextInput>("PivotY", 60.f, 30.f);
	m_InputPivotY->SetHideName(true);
	m_InputPivotY->SetTextType(ImGuiText_Type::Float);
	m_InputPivotY->SetCallback(this, &CColliderBox2DWindow::PivotYCallback);

	//Set Profile
	Label = AddWidget<CIMGUILabel>("Profile", 100.f, 30.f);

	Label->SetColor(0, 0, 255);
	Label->SetAlign(0.5f, 0.f);

	Text = AddWidget<CIMGUIText>("Profile", 60.f, 30.f);

	Text->SetColor(0, 0, 255);
	Text->SetText("Profile");
	Text->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_TextProfile = AddWidget<CIMGUIText>("TextProfile", 60.f, 30.f);

	m_TextProfile->SetColor(0, 0, 255);
	m_TextProfile->SetText(m_Profile.c_str());
	m_TextProfile->SetColor(255, 255, 255);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_InputProfile = AddWidget<CIMGUITextInput>("Profile", 60.f, 30.f);	
	m_InputProfile->SetHideName(true);
	m_InputProfile->SetTextType(ImGuiText_Type::String);
	m_InputProfile->SetCallback(this, &CColliderBox2DWindow::ProfileCallBack);

	return true;
}

void CColliderBox2DWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	if (OpenWindow())
	{
		CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

		m_Component = Hierarchy->GetSelectComponent();

		if (!m_Component->CheckType<CColliderBox2D>())
		{
			return;
		}

		CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

		Box2DInfo Info = Collider->GetInfo();

		m_Width = Info.Length.x;
		m_Height = Info.Length.y;

		std::string str = std::to_string(m_Width);
		m_TextWidth->SetText(str.c_str());

		str = std::to_string(m_Height);
		m_TextHeight->SetText(str.c_str());

		Vector3 Pos = Collider->GetOffset();

		m_PosX = Pos.x;
		m_PosY = Pos.y;

		str = std::to_string(m_PosX);
		m_TextPosX->SetText(str.c_str());

		str = std::to_string(m_PosY);
		m_TextPosY->SetText(str.c_str());

		Vector3 Pivot = Collider->GetPivot();

		m_PivotX = Pivot.x;
		m_PivotY = Pivot.y;

		str = std::to_string(m_PivotX);
		m_TextPivotX->SetText(str.c_str());

		str = std::to_string(m_PivotY);
		m_TextPivotY->SetText(str.c_str());

		m_Profile = Collider->GetCollisionProfile()->Name;

		m_TextProfile->SetText(m_Profile.c_str());
	}
}

bool CColliderBox2DWindow::IsComponent()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy->GetSelectComponent())
	{
		return false;
	}

	return true;
}

bool CColliderBox2DWindow::OpenWindow()
{
	if (!m_Component)
	{
		return false;
	}

	if (m_Component->CheckType<CColliderBox2D>())
	{
		Open();

		return true;
	}

	else
	{
		Close();

		return false;
	}
}

void CColliderBox2DWindow::WidthCallback()
{
	if (!IsComponent())
	{
		return;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	m_Component = Hierarchy->GetSelectComponent();

	if (!m_Component->CheckType<CColliderBox2D>())
	{
		return;
	}

	CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

	Box2DInfo Info = Collider->GetInfo();

	m_Width = m_InputWidth->GetValueFloat();

	Collider->SetExtent(m_Width, m_Height);
}

void CColliderBox2DWindow::HeightCallback()
{
	if (!IsComponent())
	{
		return;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	m_Component = Hierarchy->GetSelectComponent();

	if (!m_Component->CheckType<CColliderBox2D>())
	{
		return;
	}

	CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

	Box2DInfo Info = Collider->GetInfo();

	m_Height = m_InputHeight->GetValueFloat();

	Collider->SetExtent(m_Width, m_Height);
}

void CColliderBox2DWindow::PosXCallback()
{
	if (!IsComponent())
	{
		return;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	m_Component = Hierarchy->GetSelectComponent();

	if (!m_Component->CheckType<CColliderBox2D>())
	{
		return;
	}

	CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

	Vector3 Pos = Collider->GetOffset();

	Pos.x = m_InputPosX->GetValueFloat();

	Collider->SetOffset(Pos);
}

void CColliderBox2DWindow::PosYCallback()
{
	if (!IsComponent())
	{
		return;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	m_Component = Hierarchy->GetSelectComponent();

	if (!m_Component->CheckType<CColliderBox2D>())
	{
		return;
	}

	CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

	Vector3 Pos = Collider->GetOffset();

	Pos.y = m_InputPosY->GetValueFloat();

	Collider->SetOffset(Pos);
}

void CColliderBox2DWindow::PivotXCallback()
{
	if (!IsComponent())
	{
		return;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	m_Component = Hierarchy->GetSelectComponent();

	if (!m_Component->CheckType<CColliderBox2D>())
	{
		return;
	}

	CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

	Box2DInfo Info = Collider->GetInfo();

	m_PivotX = m_InputPivotX->GetValueFloat();

	Collider->SetPivot(m_PivotX, m_PivotY, 0.f);
}

void CColliderBox2DWindow::PivotYCallback()
{
	if (!IsComponent())
	{
		return;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	m_Component = Hierarchy->GetSelectComponent();

	if (!m_Component->CheckType<CColliderBox2D>())
	{
		return;
	}

	CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

	Box2DInfo Info = Collider->GetInfo();

	m_PivotY = m_InputPivotY->GetValueFloat();

	Collider->SetPivot(m_PivotX, m_PivotY, 0.f);
}

void CColliderBox2DWindow::ProfileCallBack()
{
	if (!IsComponent())
	{
		return;
	}

	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	m_Component = Hierarchy->GetSelectComponent();

	if (!m_Component->CheckType<CColliderBox2D>())
	{
		return;
	}

	CColliderBox2D* Collider = (CColliderBox2D*)m_Component;

	std::string str(m_InputProfile->GetTextMultibyte());

	Collider->GetCollisionProfile()->Name = str;
}
