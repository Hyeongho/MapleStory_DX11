#include "TalkWidget.h"
#include "../Object/NPCManager.h"
#include "../TalkManager.h"
#include "../Object/PlayerManager.h"
#include "../ClientManager.h"
#include "Fade.h"

CTalkWidget::CTalkWidget()
{
}

CTalkWidget::CTalkWidget(const CTalkWidget& window) : CWidgetWindow(window)
{
}

CTalkWidget::~CTalkWidget()
{
}

void CTalkWidget::Start()
{
}

bool CTalkWidget::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(836.f, 273);

	m_Back = CreateWidget<CImage>("Dig");
	m_NameTag = CreateWidget<CImage>("NameTag");
	m_Next = CreateWidget<CButton>("NextButton");
	m_OK = CreateWidget<CButton>("OKButton");

	m_Name = CreateWidget<CText>("Name");
	m_Name->SetAlignH(TEXT_ALIGN_H::Center);

	m_Name->SetText(L"¼³Èñ");
	m_Name->SetColor(1.0f, 1.0f, 1.0f);

	m_Talk = CreateWidget<CText>("Talk");
	m_Talk->SetColor(1.0f, 1.0f, 1.0f);

	m_Back->SetTexture("Dig", TEXT("UI/Dig/illustrationXL_big.backgrnd.png"));

	m_Back->SetSize(836.f, 169.f);
	m_Back->SetPos(1366.f / 2.f - 418.f, 0.f);
	
	m_Back->SetZOrder(-3);

	m_NameTag->SetTexture("NameTag", TEXT("UI/Dig/illustrationXL_big.nameTag.0.png"));

	m_NameTag->SetSize(196.f, 50.f);
	m_NameTag->SetPos(1366.f / 2.f + 200.f, 21.f);

	m_NameTag->SetZOrder(-2);

	m_Name->SetSize(196.f, 50.f);
	m_Name->SetPos(m_NameTag->GetWindowPos());

	m_Next->SetTexture(Button_State::Normal, "NextButton", TEXT("UI/Dig/Next/TDillustDig_big.BtNext.normal.0.png"));
	m_Next->SetTexture(Button_State::MouseOn, "NextButtonMouseOn", TEXT("UI/Dig/Next/TDillustDig_big.BtNext.mouseOver.0.png"));
	m_Next->SetTexture(Button_State::Click, "NextButtonClick", TEXT("UI/Dig/Next/TDillustDig_big.BtNext.pressed.0.png"));

	m_Next->SetClickCallback<CTalkWidget>(this, &CTalkWidget::NextClick);;

	m_Next->SetSize(84.f, 19.f);
	m_Next->SetPos(783.f, 36.f);

	m_Next->SetZOrder(-1);

	m_OK->SetTexture(Button_State::Normal, "OKButton", TEXT("UI/Dig/OK/TDillustDig_big.BtOK.normal.0.png"));
	m_OK->SetTexture(Button_State::MouseOn, "OKButtonMouseOn", TEXT("UI/Dig/OK/TDillustDig_big.BtOK.mouseOver.0.png"));
	m_OK->SetTexture(Button_State::Click, "OKButtonClick", TEXT("UI/Dig/OK/TDillustDig_big.BtOK.pressed.0.png"));

	m_OK->SetClickCallback<CTalkWidget>(this, &CTalkWidget::OKClick);

	m_OK->SetSize(84.f, 19.f);
	m_OK->SetPos(783.f, 36.f);

	m_OK->SetZOrder(-1);

	m_OK->SetVisibility(false);

	m_Talk->SetSize(m_Back->GetWindowSize());
	m_Talk->SetPos(m_Back->GetWindowPos().x + 25, m_Back->GetWindowPos().y);

	m_Talk->SetZOrder(-2);

	return true;
}

void CTalkWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CTalkWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);

	if (m_vecTalk.empty())
	{
		return;
	}
}

void CTalkWidget::Render()
{
	CWidgetWindow::Render();
}

CTalkWidget* CTalkWidget::Clone()
{
	return new CTalkWidget(*this);
}

void CTalkWidget::SetTextName(TCHAR* Name)
{
	m_Name->SetText(Name);
}

void CTalkWidget::SetTalk(int ID, const TCHAR* Name)
{
	m_vecTalk.clear();

	m_vecTalk = CTalkManager::GetInst()->FindTalk(ID);

	if (m_vecTalk[0] == L"")
	{
		return;
	}

	if (m_vecTalk.empty())
	{
		return;
	}

	m_OutputIndex = 0;

	m_Talk->SetText(m_vecTalk[m_OutputIndex]);

	m_Name->SetText(Name);
}

void CTalkWidget::NextClick()
{
	m_OutputIndex++;

	if (m_OutputIndex >= m_vecTalk.size() - 1)
	{
		m_Next->SetVisibility(false);

		m_OK->SetVisibility(true);
	}

	m_Talk->SetText(m_vecTalk[m_OutputIndex]);
}

void CTalkWidget::OKClick()
{
	std::string CurrentScene = CPlayerManager::GetInst()->GetCurrnetScene();

	if (CurrentScene == "SeolHuibang")
	{
		SetVisibility(false);

		//CClientManager::GetInst()->SetFade(true);

		CFade* Fade = (CFade*)GetViewport()->FindWidgetWindow<CFade>("FadeWidget");

		Fade->SetVisibility(true);

		CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_Start);

		Destroy();
	}

	else
	{
		return;
	}
}
