#include "ClearWidget.h"

CClearWidget::CClearWidget() : m_Play(true), m_Delay(1.4f)
{
}

CClearWidget::CClearWidget(const CClearWidget& window)
{
}

CClearWidget::~CClearWidget()
{
}

void CClearWidget::Start()
{
	CWidgetWindow::Start();
}

bool CClearWidget::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(271.f, 75.f);

	SetPos(1366.f / 2.f - 135.5f, 384.f - 37.5f);

	m_Image = CreateWidget<CImage>("Clear");

	m_Image->SetTexture("Clear", TEXT("Clear/Clear.png"));

	for (int i = 0; i < 8; i++)
	{
		m_Image->AddFrameData(Vector2(i * 271.f, 0.f), Vector2(271.f, 75.f));
	}	

	m_Image->SetSize(271.f, 75.f);

	m_Image->SetPlayTime(2.48f);
	m_Image->SetPlayScale(1.8f);

	m_Image->Enable(true);

	return true;
}

void CClearWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	int Frame = m_Image->GetFrame();

	if (Frame == 4)
	{
		m_Delay -= DeltaTime;

		if (m_Delay <= 0.f)
		{
			m_Delay = 1.4f;

			m_Image->SetFrame(++Frame);

			m_Play = true;
		}

		else
		{
			m_Play = false;
		}
	}
}

void CClearWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);

	if (m_Play)
	{
		m_Image->SetPlayScale(1.8f);
	}

	else
	{
		m_Image->SetPlayScale(0.f);
	}

	int Frame = m_Image->GetFrame();

	if (Frame == 7)
	{
		m_Image->Destroy();
	}
}

void CClearWidget::Render()
{
	CWidgetWindow::Render();
}

CClearWidget* CClearWidget::Clone()
{
	return new CClearWidget(*this);
}
