#include "ProgressBar.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"

CProgressBar::CProgressBar() : m_Percent(1.f), m_Dir(ProgressBar_Dir::RightToLeft), m_ProgressCBuffer(nullptr), m_StartMouseOn(false)
{
}

CProgressBar::CProgressBar(const CProgressBar& widget) : CWidget(widget)
{
	m_StartMouseOn = false;
	m_MouseOnCallback = nullptr;
	m_Percent = widget.m_Percent;
	m_Dir = widget.m_Dir;

	m_ProgressCBuffer = new CProgressBarConstantBuffer;

	m_ProgressCBuffer->Init();

	m_ProgressCBuffer->SetPercent(m_Percent);
	m_ProgressCBuffer->SetDir(m_Dir);
}

CProgressBar::~CProgressBar()
{
	SAFE_DELETE(m_ProgressCBuffer);
}

bool CProgressBar::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName))
		{
			return false;
		}

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CProgressBar::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, FullPath))
		{
			return false;
		}

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

void CProgressBar::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CProgressBar::SetTextureTint(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CProgressBar::AddFrameData(const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info.vecFrameData.push_back(Data);
}

void CProgressBar::Start()
{
	CWidget::Start();
}

bool CProgressBar::Init()
{
	if (!CWidget::Init())
	{
		return false;
	}

	if (m_Owner->GetViewport())
	{
		m_Shader = m_Owner->GetViewport()->GetScene()->GetResource()->FindShader("ProgressBarShader");
	}

	else
	{
		m_Shader = CResourceManager::GetInst()->FindShader("ProgressBarShader");
	}

	m_ProgressCBuffer = new CProgressBarConstantBuffer;

	m_ProgressCBuffer->Init();

	m_ProgressCBuffer->SetPercent(m_Percent);
	m_ProgressCBuffer->SetDir(m_Dir);

	return true;
}

void CProgressBar::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	if (m_MouseHovered && !m_StartMouseOn)
	{
		m_StartMouseOn = true;
		if (m_MouseOnCallback)
		{
			m_MouseOnCallback();
		}
	}

	else if (!m_MouseHovered && m_StartMouseOn)
	{
		m_StartMouseOn = false;
	}
}

void CProgressBar::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CProgressBar::Render()
{
	if (m_Info.Texture)
	{
		m_Info.Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, 0);
	}

	m_Tint = m_Info.Tint;

	m_ProgressCBuffer->UpdateCBuffer();

	CWidget::Render();
}

CProgressBar* CProgressBar::Clone()
{
	return new CProgressBar(*this);
}
