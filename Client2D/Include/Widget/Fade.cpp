#include "Fade.h"
#include "Engine.h"
#include "Device.h"
#include "../ClientManager.h"
#include "Scene/Scene.h"
#include "../ClientSceneManager.h"

CFade::CFade() : m_Opacity(1.0f)
{
}

CFade::CFade(const CFade& window) : CWidgetWindow(window)
{
}

CFade::~CFade()
{
}

void CFade::Start()
{
}

bool CFade::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(1024.f, 768.f);
	SetZOrder(INT_MAX);

	m_FadeImage = CreateWidget<CImage>("Fade");
	m_FadeImage->SetTexture("Fade", TEXT("FadeImage.png"));

	m_FadeImage->SetSize(1366.f, 768.f);
	//m_FadeImage->SetPos(100.f, 100.f);
	m_FadeImage->SetZOrder(10);
	//m_FadeImage->SetPos(1366.f / 2.f, 768.f / 2.f);

	m_FadeImage->SetVisibility(true);

	return true;
}

void CFade::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CFade::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);

	if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeIn_Start)
	{
		m_Opacity -= DeltaTime / 0.5f;

		if (m_Opacity < 0.f)
		{
			m_Opacity = 0.f;
			SetVisibility(false);
			CClientManager::GetInst()->SetFadeState(EFade_State::Normal);
			CClientManager::GetInst()->SetFade(false);
		}

		m_FadeImage->SetOpacity(m_Opacity);
	}

	if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_Start)
	{
		if (!m_Visibility)
		{
			m_Visibility = true;
		}

		m_Opacity += DeltaTime / 0.5f;

		if (m_Opacity > 1.f)
		{
			m_Opacity = 1.f;
			CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_End);

			CClientSceneManager::GetInst()->ChangeScene();
		}

		m_FadeImage->SetOpacity(m_Opacity);
	}
}

void CFade::Render()
{
	CWidgetWindow::Render();
}

CFade* CFade::Clone()
{
	return new CFade(*this);
}

void CFade::FadeIn()
{
	
}

void CFade::FadeOut()
{
	float DeltaTime =  CEngine::GetInst()->GetTimer()->GetDeltaTime();

	while (m_Opacity < 1.f)
	{
		m_Opacity += DeltaTime * 0.5f;

		m_FadeImage->SetOpacity(m_Opacity);
	}

	m_Opacity = 1.f;

	CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_End);

	/*if (CClientManager::GetInst()->GetFadeState() == EFade_State::FadeOut_Start)
	{
		if (!m_Visibility)
		{
			m_Visibility = true;
		}

		m_Opacity += DeltaTime / 0.5f;

		if (m_Opacity > 1.f)
		{
			m_Opacity = 1.f;
			CClientManager::GetInst()->SetFadeState(EFade_State::FadeOut_End);
		}

		m_FadeImage->SetOpacity(m_Opacity);
	}*/
}
