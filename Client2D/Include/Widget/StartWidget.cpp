#include "StartWidget.h"
#include "Engine.h"
#include "../Scene/LoadingScene.h"
#include "../Scene/MainScene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "../Object/PlayerManager.h"
#include "../ClientManager.h"
#include "Fade.h"

CStartWidget::CStartWidget()
{
}

CStartWidget::CStartWidget(const CStartWidget& window) : CWidgetWindow(window)
{
	m_Male = FindWidget<CButton>("MaleButton");
	m_Female = FindWidget<CButton>("FemaleButton");
}

CStartWidget::~CStartWidget()
{
}

void CStartWidget::Start()
{
}

bool CStartWidget::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(1024.f, 768.f);

	m_Male = CreateWidget<CButton>("MaleButton");
	m_Female = CreateWidget<CButton>("FemaleButton");
	m_Back = CreateWidget<CImage>("Back");

	m_Male->SetZOrder(1);
	m_Female->SetZOrder(1);

	m_Back->SetTexture("Back", TEXT("CustomizeChar.dualBlade.0.0.png"));
	m_Back->SetSize(1366.f, 768.f);

    m_Male->SetPos(1366.f / 2.f - 100.f, 768.f / 2.f - 58.5f);
    m_Male->SetSize(81.f, 117.f);
    m_Male->SetTexture(Button_State::Normal, "MaleButton", TEXT("genderSelect.male.normal.0.png"));
    m_Male->SetTexture(Button_State::MouseOn, "MaleButtonMouseOn", TEXT("genderSelect.male.mouseOver.0.png"));
    m_Male->SetTexture(Button_State::Click, "MaleButtonClick", TEXT("genderSelect.male.pressed.0.png"));

	/*m_Male->SetTextureFullPath(Button_State::Normal, "MaleButton", TEXT("genderSelect.male.normal.0.png"));
	m_Male->SetTextureFullPath(Button_State::MouseOn, "MaleButton", TEXT("genderSelect.male.mouseOver.0.png"));
	m_Male->SetTextureFullPath(Button_State::Click, "MaleButton", TEXT("genderSelect.male.pressed.0.png"));*/

    m_Male->SetClickCallback<CStartWidget>(this, &CStartWidget::MaleClick);

    m_Female->SetPos(1366.f / 2.f + 100.f, 768.f / 2.f - 58.5f);
    m_Female->SetSize(81.f, 117.f);
    m_Female->SetTexture(Button_State::Normal, "FemaleButton", TEXT("genderSelect.female.normal.0.png"));
    m_Female->SetTexture(Button_State::MouseOn, "FemaleButtonMouseOn", TEXT("genderSelect.female.mouseOver.0.png"));
    m_Female->SetTexture(Button_State::Click, "FemaleButtonClick", TEXT("genderSelect.female.pressed.0.png"));

	/*m_Female->SetTextureFullPath(Button_State::Normal, "MaleButton", TEXT("genderSelect.male.normal.0.png"));
	m_Female->SetTextureFullPath(Button_State::MouseOn, "FemaleButtonMouseOn", TEXT("genderSelect.male.mouseOver.0.png"));
	m_Female->SetTextureFullPath(Button_State::Click, "FemaleButtonClick", TEXT("genderSelect.male.pressed.0.png"));*/

    m_Female->SetClickCallback<CStartWidget>(this, &CStartWidget::FemaleClick);

	return true;
}

void CStartWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CStartWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);

	if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_End)
	{
		CClientManager::GetInst()->SetFadeState(EFade_State::Normal);

		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CLoadingScene>(false);
	}
}

void CStartWidget::Render()
{
	CWidgetWindow::Render();
}

CStartWidget* CStartWidget::Clone()
{
	return new CStartWidget(*this);
}

void CStartWidget::MaleClick()
{
	CPlayerManager::GetInst()->SetGender(Gender::Male);

	CFade* Fade = (CFade*)GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

	Fade->SetVisibility(true);

	CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_Start);

	Fade->FadeOut();

	/*CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CLoadingScene>(false);*/
}

void CStartWidget::FemaleClick()
{
	CPlayerManager::GetInst()->SetGender(Gender::Female);

	CFade* Fade = (CFade*)GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

	Fade->SetVisibility(true);

	CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_Start);

	//Fade->FadeOut();

	/*CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CLoadingScene>(false);*/
}
