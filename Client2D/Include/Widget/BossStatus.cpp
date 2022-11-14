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

	SetPos(RS.Width / 2.f - 400.5f, RS.Height - 40.f);

	SetSize(801.f, 40.f);

	m_StausBackGrond = CreateWidget<CImage>("BossStausBackGrond");
	m_StausBackGrond->SetTexture("BossStausBackGrond", TEXT("MobGage/boss_hp.backgrnd.png"));
	m_StausBackGrond->SetSize(801.f, 40.f);

	m_HPBar = CreateWidget<CProgressBar>("BossHPBar");
	m_HPBar->SetTexture("BossHPBar", TEXT("MobGage/BossHP.png"));
	m_HPBar->SetSize(758.f, 12.f);
	m_HPBar->SetPos(39.f, 24.f);

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
