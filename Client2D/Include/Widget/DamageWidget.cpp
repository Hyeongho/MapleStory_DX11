#include "DamageWidget.h"

CDamageWidget::CDamageWidget() : m_Opacity(1.0f)
{
}

CDamageWidget::CDamageWidget(const CDamageWidget& window) : CWidgetWindow(window)
{
	m_Number = window.m_Number;
}

CDamageWidget::~CDamageWidget()
{
	auto iter = m_vecFileName.begin();
	auto iterEnd = m_vecFileName.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE_ARRAY((*iter));
	}
}

void CDamageWidget::SetNumber(float Damage)
{
	m_Number->SetNumber((int)Damage);
}

void CDamageWidget::Start()
{
	CWidgetWindow::Start();
}

bool CDamageWidget::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	m_Number = CreateWidget<CNumber>("Number");

	for (int i = 0; i < 10; ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Damage/Attack/%d.png"), i);

		m_vecFileName.push_back(FileName);
	}

	m_Number->SetTexture("Number", m_vecFileName);
	m_Number->AddFrameData(10);

	return true;
}

void CDamageWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CDamageWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CDamageWidget::Render()
{
	CWidgetWindow::Render();
}

CDamageWidget* CDamageWidget::Clone()
{
	return new CDamageWidget(*this);
}
