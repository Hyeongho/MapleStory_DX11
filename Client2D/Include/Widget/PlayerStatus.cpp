#include "PlayerStatus.h"
#include "Engine.h"
#include "Device.h"

CPlayerStatus::CPlayerStatus()
{
}

CPlayerStatus::CPlayerStatus(const CPlayerStatus& window) : CWidgetWindow(window)
{
    m_StausCover = FindWidget<CImage>("StausCover");
    m_StausBackGrond = FindWidget<CImage>("StausBackGrond");
    m_HPBar = FindWidget<CProgressBar>("HPBar");
    m_MPBar = FindWidget<CProgressBar>("MPBar");
}

CPlayerStatus::~CPlayerStatus()
{
}

void CPlayerStatus::SetHPPercent(float Percent)
{
    m_HPBar->SetPercent(Percent);
}

void CPlayerStatus::SetHPDir(ProgressBar_Dir Dir)
{
    m_HPBar->SetDir(Dir);
}

void CPlayerStatus::SetMPPercent(float Percent)
{
    m_MPBar->SetPercent(Percent);
}

void CPlayerStatus::SetMPDir(ProgressBar_Dir Dir)
{
    m_MPBar->SetDir(Dir);
}

void CPlayerStatus::Start()
{
}

bool CPlayerStatus::Init()
{
    if (!CWidgetWindow::Init())
    {
        return false;
    }

    Resolution RS = CDevice::GetInst()->GetResolution();

    SetPos(RS.Width / 2.f - 102.f, 30.f);

    SetSize(204.f, 70.f);

    m_StausCover = CreateWidget<CImage>("StausCover");
    m_StausCover->SetTexture("StausCover", TEXT("UI/Satatus/mainBar.status.layercover.png"));
    m_StausCover->SetSize(204.f, 70.f);

    m_StausCover->SetZOrder(5);

    m_HPBar = CreateWidget<CProgressBar>("HPBar");
    m_HPBar->SetTexture("HPBar", TEXT("UI/Satatus/mainBar.status.gauge.hp.layer0.png"));
    m_HPBar->SetSize(171.f, 13.f);

    m_HPBar->SetPos(24.f, 28.f);

    m_HPBar->SetZOrder(2);

    m_MPBar = CreateWidget<CProgressBar>("MPBar");
    m_MPBar->SetTexture("MPBar", TEXT("UI/Satatus/mainBar.status.gauge.mp.layer0.png"));
    m_MPBar->SetSize(171.f, 13.f);

    m_MPBar->SetPos(24.f, 14.f);

    m_MPBar->SetZOrder(2);

    m_StausBackGrond = CreateWidget<CImage>("StausBackGrond");
    m_StausBackGrond->SetTexture("StausBackGrond", TEXT("UI/Satatus/mainBar.status.backgrnd.png"));
    m_StausBackGrond->SetSize(198.f, 37.f);

    m_StausBackGrond->SetPos(2.f, 12.f);

    m_StausBackGrond->SetZOrder(1);

    return true;
}

void CPlayerStatus::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);
}

void CPlayerStatus::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerStatus::Render()
{
    CWidgetWindow::Render();
}

CPlayerStatus* CPlayerStatus::Clone()
{
    return new CPlayerStatus(*this);
}
