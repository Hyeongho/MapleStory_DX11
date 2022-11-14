#include "BossStatus.h"
#include "Engine.h"
#include "Device.h"

CBossStatus::CBossStatus()
{
}

CBossStatus::CBossStatus(const CBossStatus& window) : CWidgetWindow(window)
{
}

CBossStatus::~CBossStatus()
{
}

void CBossStatus::SetText(const TCHAR* Text)
{
}

void CBossStatus::SetHPPercent(float Percent)
{
	m_HPBar->SetPercent(Percent);
}

void CBossStatus::SetHPDir(ProgressBar_Dir Dir)
{
	m_HPBar->SetDir(Dir);
}

void CBossStatus::SetMPPercent(float Percent)
{
}

void CBossStatus::SetMPDir(ProgressBar_Dir Dir)
{
}

void CBossStatus::Start()
{
}

bool CBossStatus::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution RS = CDevice::GetInst()->GetResolution();

	return true;
}

void CBossStatus::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CBossStatus::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBossStatus::Render()
{
	CWidgetWindow::Render();
}

CBossStatus* CBossStatus::Clone()
{
	return new CBossStatus(*this);
}
