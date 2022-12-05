#include "QuesetWidget.h"

CQuesetWidget::CQuesetWidget() : m_Opacity(1.f)
{
}

CQuesetWidget::CQuesetWidget(const CQuesetWidget& window)
{
}

CQuesetWidget::~CQuesetWidget()
{
}

void CQuesetWidget::Start()
{
	CWidgetWindow::Start();
}

bool CQuesetWidget::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(300.f, 300.f);

	SetPos(1366.f / 2.f - 150.f, 576.f - 150.f);

	m_Text = CreateWidget<CText>("Text");

	m_Text->SetColor(1.f, 0.498f, 0.f);

	m_Text->SetFontSize(36.f);

	m_Text->SetSize(300.f, 300.f);

	m_Text->SetAlignH(TEXT_ALIGN_H::Center);
	m_Text->SetAlignV(TEXT_ALIGN_V::Middle);

	SetVisibility(false);

	return true;
}

void CQuesetWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (GetVisibility())
	{
		m_Opacity -= DeltaTime / 2.0f;

		if (m_Opacity < 0.f)
		{
			SetVisibility(false);

			return;
		}

		m_Text->SetOpacity(m_Opacity);
	}
}

void CQuesetWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CQuesetWidget::Render()
{
	CWidgetWindow::Render();
}

CQuesetWidget* CQuesetWidget::Clone()
{
	return new CQuesetWidget(*this);
}

void CQuesetWidget::SetText(std::string Text)
{
	std::wstring wStr;

	wStr.assign(Text.begin(), Text.end());

	m_Text->SetText(wStr.c_str());

	SetVisibility(true);

	/*float PosX = (1366.f / 2.f - 150.f) - (36.f * Text.size());

	SetPos(PosX, 576.f - 150.f);*/

	m_Opacity = 1.f;
}
