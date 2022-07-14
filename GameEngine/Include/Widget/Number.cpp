#include "Number.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../Resource/Shader/WidgetConstantBuffer.h"

CNumber::CNumber() : m_Number(0), m_Opacity(0.5f)
{
}

CNumber::CNumber(const CNumber& widget) : CWidget(widget)
{
	m_Number = widget.m_Number;
}

CNumber::~CNumber()
{
}

bool CNumber::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
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

bool CNumber::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
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

bool CNumber::SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
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

bool CNumber::SetTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath)
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

void CNumber::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CNumber::SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CNumber::AddFrameData(const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info.vecFrameData.push_back(Data);
}

void CNumber::AddFrameData(int Count)
{
	for (int i = 0; i < Count; i++)
	{
		AnimationFrameData	Data;
		Data.Start = Vector2(0.f, 0.f);
		Data.Size = Vector2((float)m_Info.Texture->GetWidth(i), (float)m_Info.Texture->GetHeight(i));

		m_Info.vecFrameData.push_back(Data);
	}
}

void CNumber::Start()
{
	CWidget::Start();
}

bool CNumber::Init()
{
	if (!CWidget::Init())
	{
		return false;
	}

	if (m_Owner->GetViewport())
	{
		m_Shader = m_Owner->GetViewport()->GetScene()->GetResource()->FindShader("NumberShader");
	}

	else
	{
		m_Shader = CResourceManager::GetInst()->FindShader("NumberShader");
	}

	return true;
}

void CNumber::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
}

void CNumber::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CNumber::Render()
{
	// 현재 숫자를 분리한다.
	int	Number = m_Number;

	m_vecNumber.clear();

	if (Number == 0)
	{
		m_vecNumber.push_back(0);
	}

	else
	{
		std::stack<int>	stackNumber;

		// 12340
		// stack : 0, 4, 3, 2, 1
		while (Number > 0)
		{
			stackNumber.push(Number % 10);
			Number /= 10;
		}

		while (!stackNumber.empty())
		{
			m_vecNumber.push_back(stackNumber.top());
			stackNumber.pop();
		}
	}

	m_CBuffer->SetAnimEnable(false);

	size_t Count = m_vecNumber.size();

	for (size_t i = 0; i < Count; i++)
	{
		Vector2 Offset;

		if (m_Info.Texture)
		{
			int	Frame = 0;
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
				Frame = m_vecNumber[i];

				m_CBuffer->SetStartUV(Vector2(0.f, 0.f));
				m_CBuffer->SetEndUV(Vector2(1.f, 1.f));

				m_Size = Vector2((float)m_Info.Texture->GetWidth(Frame), (float)m_Info.Texture->GetHeight(Frame));

				if (i > 0)
				{
					int PrevFrame = m_vecNumber[i - 1];
					Offset = Vector2((float)m_Info.Texture->GetWidth(PrevFrame), (float)m_Info.Texture->GetHeight(PrevFrame));
				}

				break;
			case Image_Type::Array:
				break;
			}

			m_Info.Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, Frame);
		}

		m_Tint = m_Info.Tint;

		m_CBuffer->SetOpacity(m_Opacity);

		//m_RenderPos.x += (m_Size.x * (float)i);
		m_RenderPos.x += Offset.x;

		CWidget::Render();
	}
}

CNumber* CNumber::Clone()
{
	return new CNumber(*this);
}
