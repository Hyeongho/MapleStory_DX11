#include "Image.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../Resource/Shader/WidgetConstantBuffer.h"

CImage::CImage()
{
}

CImage::CImage(const CImage& widget) : CWidget(widget)
{
	m_ClickCallback = nullptr;
}

CImage::~CImage()
{
}

bool CImage::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
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

bool CImage::SetTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
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

	return true;
}

bool CImage::SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, vecFileName, PathName))
		{
			return false;
		}

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CImage::SetTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, vecFullPath))
		{
			return false;
		}

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}


	SetUseTexture(true);

	return true;
}

void CImage::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CImage::SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CImage::AddFrameData(const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info.vecFrameData.push_back(Data);
}

void CImage::AddFrameData(int Count)
{
	for (int i = 0; i < Count; i++)
	{
		AnimationFrameData	Data;
		Data.Start = Vector2(0.f, 0.f);
		Data.Size = Vector2((float)m_Info.Texture->GetWidth(i), (float)m_Info.Texture->GetHeight(i));

		m_Info.vecFrameData.push_back(Data);
	}
}

void CImage::SetPlayTime(float PlayTime)
{
	m_Info.PlayTime = PlayTime;
}

void CImage::SetPlayScale(float PlayScale)
{
	m_Info.PlayScale = PlayScale;
}

void CImage::Start()
{
	CWidget::Start();
}

bool CImage::Init()
{
	if (!CWidget::Init())
	{
		return false;
	}

	return true;
}

void CImage::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
}

void CImage::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);

	if (!m_Info.vecFrameData.empty())
	{
		m_Info.Time += DeltaTime * m_Info.PlayScale;

		m_Info.FrameTime = m_Info.PlayTime / m_Info.vecFrameData.size();

		if (m_Info.Time >= m_Info.FrameTime)
		{
			m_Info.Time -= m_Info.FrameTime;

			m_Info.Frame++;

			if (m_Info.Frame == (int)m_Info.vecFrameData.size())
			{
				m_Info.Frame = 0;
			}
		}
	}
}

void CImage::Render()
{
	int	Frame = 0;

	if (!m_Info.vecFrameData.empty())
	{
		m_CBuffer->SetAnimEnable(true);
		m_CBuffer->SetAnimType((int)m_Info.Texture->GetImageType());

		switch (m_Info.Texture->GetImageType())
		{
		case Image_Type::Atlas:
		{
			Vector2	StartUV, EndUV;

			Vector2	Start = m_Info.vecFrameData[m_Info.Frame].Start;
			Vector2	FrameSize = m_Info.vecFrameData[m_Info.Frame].Size;

			StartUV = Start / Vector2((float)m_Info.Texture->GetWidth(), (float)m_Info.Texture->GetHeight());

			EndUV = (Start + FrameSize) / Vector2((float)m_Info.Texture->GetWidth(), (float)m_Info.Texture->GetHeight());

			m_CBuffer->SetStartUV(StartUV);
			m_CBuffer->SetEndUV(EndUV);
		}
		break;
		case Image_Type::Frame:
			Frame = m_Info.Frame;

			m_CBuffer->SetStartUV(Vector2(0.f, 0.f));
			m_CBuffer->SetEndUV(Vector2(1.f, 1.f));
			break;
		case Image_Type::Array:
			break;
		}

	}

	else
	{
		m_CBuffer->SetAnimEnable(false);
	}


	if (m_Info.Texture)
	{
		m_Info.Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, Frame);
	}

	m_Tint = m_Info.Tint;

	CWidget::Render();
}

CImage* CImage::Clone()
{
	return new CImage(*this);
}
