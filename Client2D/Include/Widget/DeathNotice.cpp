#include "DeathNotice.h"
#include "Engine.h"
#include "Device.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "../ClientManager.h"
#include "Fade.h"

CDeathNotice::CDeathNotice()
{
}

CDeathNotice::CDeathNotice(const CDeathNotice& window)
{
}

CDeathNotice::~CDeathNotice()
{
}

void CDeathNotice::Start()
{
}

bool CDeathNotice::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution RS = CDevice::GetInst()->GetResolution();

	SetSize(300.f, 131.f);
	SetPos(RS.Width / 2.f - 150.f, RS.Height / 2.f - 65.5f);

	m_Image = CreateWidget<CImage>("Image");
	m_Button = CreateWidget<CButton>("Button");

	m_Image->SetTexture("Image", TEXT("Notice/Notice.0.png"));

	m_Button->SetTexture(Button_State::Normal, "Normal", TEXT("Notice/Notice.btOK.normal.0.png"));
	m_Button->SetTexture(Button_State::MouseOn, "MouseOn", TEXT("Notice/Notice.btOK.mouseOver.0.png"));
	m_Button->SetTexture(Button_State::Click, "Click", TEXT("Notice/Notice.btOK.pressed.0.png"));

	m_Button->SetClickCallback<CDeathNotice>(this, &CDeathNotice::ClickCallBack);

	m_Image->SetSize(300.f, 131.f);
	m_Button->SetSize(40.f, 16.f);

	m_Button->SetPos(240.f, 15.f);

	m_Image->SetZOrder(6);
	m_Button->SetZOrder(7);

	SetVisibility(false);

	return true;
}

void CDeathNotice::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CDeathNotice::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CDeathNotice::Render()
{
	CWidgetWindow::Render();
}

CDeathNotice* CDeathNotice::Clone()
{
	return new CDeathNotice(*this);
}

void CDeathNotice::ClickCallBack()
{
	CFade* Fade = GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

	Fade->SetVisibility(true);

	CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_Start);
}
