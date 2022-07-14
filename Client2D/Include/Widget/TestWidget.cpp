#include "TestWidget.h"
#include "Engine.h"
#include "../Scene/LoadingScene.h"
#include "Scene/SceneManager.h"

CTestWidget::CTestWidget()
{
}

CTestWidget::CTestWidget(const CTestWidget& window) : CWidgetWindow(window)
{
	m_Button1 = FindWidget<CButton>("Button1");
	m_Button2 = FindWidget<CButton>("Button2");
}

CTestWidget::~CTestWidget()
{
}

void CTestWidget::Start()
{
}

bool CTestWidget::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(1366.f, 728.f);

	m_Button1 = CreateWidget<CButton>("Button1");

	m_Button1->SetPos((1366.f / 4.f) - (200.f / 2), 728.f / 2.f);
	m_Button1->SetSize(200.f, 50.f);

	m_Button1->SetTextureTint(Button_State::Normal, 0, 0, 0, 255);
	m_Button1->SetTextureTint(Button_State::MouseOn, 220, 220, 220, 255);
	m_Button1->SetTextureTint(Button_State::Click, 150, 150, 150, 255);

	m_Button1->SetClickCallback<CTestWidget>(this, &CTestWidget::Button1Click);

	m_Button2 = CreateWidget<CButton>("Button2");

	m_Button2->SetPos(((1366.f / 4.f) * 3.f) - (200.f / 2), 728.f / 2.f);
	m_Button2->SetSize(200.f, 50.f);

	m_Button2->SetTextureTint(Button_State::Normal, 0, 0, 0, 255);
	m_Button2->SetTextureTint(Button_State::MouseOn, 220, 220, 220, 255);
	m_Button2->SetTextureTint(Button_State::Click, 150, 150, 150, 255);

	m_Button2->SetClickCallback<CTestWidget>(this, &CTestWidget::Button2Click);

	return true;
}

void CTestWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	float a = m_Button1->GetWindowPos().x;
	float b = m_Button2->GetWindowPos().x;
}

void CTestWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CTestWidget::Render()
{
	CWidgetWindow::Render();
}

CTestWidget* CTestWidget::Clone()
{
	return new CTestWidget(*this);
}

void CTestWidget::Button1Click()
{

}

void CTestWidget::Button2Click()
{
	CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CLoadingScene>(false);
}
