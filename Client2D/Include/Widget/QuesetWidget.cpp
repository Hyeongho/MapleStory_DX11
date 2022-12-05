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

	m_Text = CreateWidget<CText>("Text");

	SetVisibility(false);

	return true;
}

void CQuesetWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (GetVisibility())
	{
		m_Opacity -= DeltaTime - 2.0f;

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

	m_Opacity = 1.f;
}
