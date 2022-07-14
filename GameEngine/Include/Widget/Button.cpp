#include "Button.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"

CButton::CButton() : m_State(Button_State::Normal), m_MouseOnSound(false), m_ClickSound(false)
{
}

CButton::CButton(const CButton& widget) : CWidget(widget)
{
	m_State = Button_State::Normal;
	m_ClickCallback = nullptr;
	m_MouseOnSound = false;
	m_ClickSound = false;
}

CButton::~CButton()
{
}

bool CButton::SetTexture(Button_State State, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName))
		{
			return false;
		}

		m_Info[(int)State].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		{
			return false;
		}

		m_Info[(int)State].Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CButton::SetTextureFullPath(Button_State State, const std::string& Name, const TCHAR* FullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, FullPath))
		{
			return false;
		}

		m_Info[(int)State].Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
		{
			return false;
		}

		m_Info[(int)State].Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

void CButton::SetTextureTint(Button_State State, const Vector4& Tint)
{
	m_Info[(int)State].Tint = Tint;
}

void CButton::SetTextureTint(Button_State State, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_Info[(int)State].Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CButton::AddFrameData(Button_State State, const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info[(int)State].vecFrameData.push_back(Data);
}

void CButton::SetPlayTime(Button_State State, float PlayTime)
{
	m_Info[(int)State].PlayTime = PlayTime;
}

void CButton::SetPlayScale(Button_State State, float PlayScale)
{
	m_Info[(int)State].PlayScale = PlayScale;
}

void CButton::SetSound(Button_Sound_State State, const std::string& Name)
{
	if (m_Owner->GetViewport())
	{
		m_Sound[(int)State] = m_Owner->GetViewport()->GetScene()->GetResource()->FindSound(Name);
	}

	else
	{
		m_Sound[(int)State] = CResourceManager::GetInst()->FindSound(Name);
	}
}

void CButton::SetSound(Button_Sound_State State, CSound* Sound)
{
	m_Sound[(int)State] = Sound;
}

void CButton::SetSound(Button_Sound_State State, const std::string& ChannelGroupName, const std::string& Name, 
	const char* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		m_Owner->GetViewport()->GetScene()->GetResource()->LoadSound(ChannelGroupName, false, Name, FileName, PathName);

		m_Sound[(int)State] = m_Owner->GetViewport()->GetScene()->GetResource()->FindSound(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadSound(ChannelGroupName, false, Name, FileName, PathName);

		m_Sound[(int)State] = CResourceManager::GetInst()->FindSound(Name);
	}
}

void CButton::Start()
{
	CWidget::Start();

	for (int i = 0; i < (int)Button_State::Max; i++)
	{
		if (!m_Info[i].vecFrameData.empty())
		{
			m_Info[i].FrameTime = m_Info[i].PlayTime / m_Info[i].vecFrameData.size();
		}
	}
}

bool CButton::Init()
{
	if (!CWidget::Init())
	{
		return false;
	}

	return true;
}

void CButton::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	if (m_State != Button_State::Disable)
	{
		if (m_MouseHovered)
		{
			if (!m_MouseOnSound)
			{
				m_MouseOnSound = true;

				if (m_Sound[(int)Button_Sound_State::MouseOn])
				{
					m_Sound[(int)Button_Sound_State::MouseOn]->Play();
				}
			}

			if (CInput::GetInst()->GetMouseLButtonClick())
			{
				m_State = Button_State::Click;

				if (!m_ClickSound)
				{
					m_ClickSound = true;

					if (m_Sound[(int)Button_Sound_State::Click])
					{
						m_Sound[(int)Button_Sound_State::Click]->Play();
					}
				}
			}

			else if (m_State == Button_State::Click)
			{
				if (m_ClickCallback)
				{
					m_ClickCallback();
				}

				m_State = Button_State::MouseOn;
				m_ClickSound = false;
			}

			else
			{
				m_ClickSound = false;
				m_State = Button_State::MouseOn;
			}
		}

		else
		{
			m_ClickSound = false;
			m_MouseOnSound = false;
			m_State = Button_State::Normal;
		}
	}
}

void CButton::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CButton::Render()
{
	if (m_Info[(int)m_State].Texture)
	{
		m_Info[(int)m_State].Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, 0);
	}

	m_Tint = m_Info[(int)m_State].Tint;
	//m_Texture = m_Info[(int)m_State].Texture;

	if (m_State == Button_State::Click)
	{
		CWidget::Render();
	}

	CWidget::Render();
}

CButton* CButton::Clone()
{
	return new CButton(*this);
}
