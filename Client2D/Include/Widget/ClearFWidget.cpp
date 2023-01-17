#include "ClearFWidget.h"

CClearFWidget::CClearFWidget()
{
}

CClearFWidget::CClearFWidget(const CClearFWidget& window)
{
}

CClearFWidget::~CClearFWidget()
{
}

void CClearFWidget::Start()
{
	CWidgetWindow::Start();
}

bool CClearFWidget::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(418.f, 158.f);

	SetPos(1366.f / 2.f - 209.f, 384.f - 79.f);

	m_Image = CreateWidget<CImage>("ClearF");

	m_Image->SetTexture("ClearF", TEXT("ClearF/ClearF.png"));

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_Image->AddFrameData(Vector2(i * 418.f, 0.f), Vector2(418.f, 158.f));
		}
	}

	for (int i = 0; i < 20; i++)
	{
		m_Image->AddFrameData(Vector2(7 * 418.f, 0.f), Vector2(418.f, 158.f));
	}

	for (int i = 8; i < 12; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_Image->AddFrameData(Vector2(i * 418.f, 0.f), Vector2(418.f, 158.f));
		}
	}

	m_Image->SetSize(418.f, 158.f);

	m_Image->SetPlayTime(3.18f);

	m_Image->Enable(true);

	return true;
}

void CClearFWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CClearFWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);

	int Frame = m_Image->GetFrame();

	if (Frame == 53)
	{
		m_Image->Destroy();
	}
}

void CClearFWidget::Render()
{
	CWidgetWindow::Render();
}

CClearFWidget* CClearFWidget::Clone()
{
	return new CClearFWidget(*this);
}
