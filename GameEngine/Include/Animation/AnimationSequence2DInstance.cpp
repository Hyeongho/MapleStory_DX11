#include "AnimationSequence2DInstance.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Component/SpriteComponent.h"
#include "../Resource/Animation/AnimationSequence2D.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"
#include "../Resource/Texture/Texture.h"

CAnimationSequence2DInstance::CAnimationSequence2DInstance() : m_Scene(nullptr), m_Owner(nullptr), m_PlayAnimation(true), m_Flip(true)
{
	SetTypeID<CAnimationSequence2DInstance>();
}

CAnimationSequence2DInstance::CAnimationSequence2DInstance(const CAnimationSequence2DInstance& Anim)
{
	m_PlayAnimation = Anim.m_PlayAnimation;

	auto iter = Anim.m_mapAnimation.begin();
	auto iterEnd = Anim.m_mapAnimation.end();

	for (; iter != iterEnd; iter++)
	{
		CAnimationSequence2DData* Data = new CAnimationSequence2DData;

		Data->m_Sequence = iter->second->m_Sequence;
		Data->m_Name = iter->second->m_Name;
		Data->m_Loop = iter->second->m_Loop;
		Data->m_PlayTime = iter->second->m_PlayTime;
		Data->m_PlayScale = iter->second->m_PlayScale;
		Data->m_Reverse = iter->second->m_Reverse;

		if (Anim.m_CurrentAnimation->m_Name == Data->m_Name)
		{
			m_CurrentAnimation = Data;
		}

		m_mapAnimation.insert(std::make_pair(iter->first, Data));
	}
}

CAnimationSequence2DInstance::~CAnimationSequence2DInstance()
{
	auto iter = m_mapAnimation.begin();
	auto iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}
}

void CAnimationSequence2DInstance::AddAnimation(const std::string& SequenceName, const std::string& Name, bool Loop, float PlayTime, float PlayScale, bool Reverse)
{
	CAnimationSequence2DData* Anim = FindAnimation(Name);

	if (Anim)
	{
		return;
	}

	CAnimationSequence2D* Sequence = nullptr;

	if (m_Scene)
	{
		Sequence = m_Scene->GetResource()->FindAnimationSequence2D(SequenceName);
	}

	else
	{
		Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(SequenceName);
	}

	if (!Sequence)
	{
		return;
	}

	Anim = new CAnimationSequence2DData;

	Anim->m_Sequence = Sequence;
	Anim->m_Name = Name;
	Anim->m_Loop = Loop;
	Anim->m_PlayTime = PlayTime;
	Anim->m_PlayScale = PlayScale;
	Anim->m_Reverse = Reverse;
	Anim->m_FrameTime = PlayTime / Sequence->GetFrameCount();

	if (m_mapAnimation.empty())
	{
		m_CurrentAnimation = Anim;

		if (m_Owner)
		{
			CTexture* Texture = Anim->m_Sequence->GetTexture();

			m_Owner->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, Texture->GetName(), Texture);
		}
	}

	m_mapAnimation.insert(std::make_pair(Name, Anim));
}

void CAnimationSequence2DInstance::AddAnimation(const TCHAR* FileName, const std::string& PathName, const std::string& Name, bool Loop, float PlayTime, float PlayScale, bool Reverse)
{
	CAnimationSequence2DData* Anim = FindAnimation(Name);

	if (Anim)
	{
		return;
	}

	char FileNameMultibyte[256] = {};

	int	Length = WideCharToMultiByte(CP_ACP, 0, FileName, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_ACP, 0, FileName, -1, FileNameMultibyte, Length, 0, 0);

	CAnimationSequence2D* Sequence = nullptr;

	if (m_Scene)
	{
		std::string	SequenceName;

		m_Scene->GetResource()->LoadSequence2D(SequenceName, FileNameMultibyte);
		Sequence = m_Scene->GetResource()->FindAnimationSequence2D(SequenceName);
	}

	else
	{
		std::string	SequenceName;

		CResourceManager::GetInst()->LoadSequence2D(SequenceName, FileNameMultibyte);
		Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(SequenceName);
	}

	if (!Sequence)
	{
		return;
	}

	Anim = new CAnimationSequence2DData;

	Anim->m_Sequence = Sequence;
	Anim->m_Name = Name;
	Anim->m_Loop = Loop;
	Anim->m_PlayTime = PlayTime;
	Anim->m_PlayScale = PlayScale;
	Anim->m_Reverse = Reverse;
	Anim->m_FrameTime = PlayTime / Sequence->GetFrameCount();

	if (m_mapAnimation.empty())
	{
		m_CurrentAnimation = Anim;

		if (m_Owner)
		{
			m_Owner->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, Anim->m_Sequence->GetTexture()->GetName(), Anim->m_Sequence->GetTexture());
		}
	}

	m_mapAnimation.insert(std::make_pair(Name, Anim));
}

void CAnimationSequence2DInstance::SetPlayTime(const std::string& Name, float PlayTime)
{
	CAnimationSequence2DData* Anim = FindAnimation(Name);

	if (!Anim)
	{
		return;
	}

	Anim->m_PlayTime = PlayTime;
}

void CAnimationSequence2DInstance::SetPlayScale(const std::string& Name, float PlayScale)
{
	CAnimationSequence2DData* Anim = FindAnimation(Name);

	if (!Anim)
	{
		return;
	}

	Anim->m_PlayScale = PlayScale;
}

void CAnimationSequence2DInstance::SetReverse(const std::string& Name, bool Reverse)
{
	CAnimationSequence2DData* Anim = FindAnimation(Name);

	if (!Anim)
	{
		return;
	}

	Anim->m_Reverse = Reverse;
}

void CAnimationSequence2DInstance::SetLoop(const std::string& Name, bool Loop)
{
	CAnimationSequence2DData* Anim = FindAnimation(Name);

	if (!Anim)
	{
		return;
	}

	Anim->m_Loop = Loop;
}

void CAnimationSequence2DInstance::SetCurrentAnimation(const std::string& Name)
{
	m_CurrentAnimation = FindAnimation(Name);

	if (!m_CurrentAnimation)
	{
		return;
	}

	m_CurrentAnimation->m_Frame = 0;
	m_CurrentAnimation->m_Time = 0.f;

	size_t Size = m_CurrentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_CurrentAnimation->m_vecNotify[i]->Call = false;
	}

	if (m_Owner)
	{
		m_Owner->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, m_CurrentAnimation->m_Sequence->GetTexture()->GetName(), m_CurrentAnimation->m_Sequence->GetTexture());
		m_Owner->SetTextureFrameIndex(0);
	}
}

void CAnimationSequence2DInstance::SetCurrent(CAnimationSequence2DData* CurrentAnimation)
{
	m_CurrentAnimation = CurrentAnimation;
}

void CAnimationSequence2DInstance::ChangeAnimation(const std::string& Name)
{
	if (m_CurrentAnimation->m_Name == Name)
	{
		return;
	}

	m_CurrentAnimation->m_Frame = 0;
	m_CurrentAnimation->m_Time = 0.f;

	size_t	Size = m_CurrentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_CurrentAnimation->m_vecNotify[i]->Call = false;
	}

	m_CurrentAnimation = FindAnimation(Name);
	m_CurrentAnimation->m_Frame = 0;
	m_CurrentAnimation->m_Time = 0.f;

	if (m_Owner)
	{
		m_Owner->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, m_CurrentAnimation->m_Sequence->GetTexture()->GetName(), m_CurrentAnimation->m_Sequence->GetTexture());
		m_Owner->SetTextureFrameIndex(0);
	}
}

bool CAnimationSequence2DInstance::CheckCurrentAnimation(const std::string& Name)
{
	return m_CurrentAnimation->m_Name == Name;
}

void CAnimationSequence2DInstance::AnimationReStart()
{
	m_CurrentAnimation->m_Frame = 0;
	m_CurrentAnimation->m_Time = 0.f;
}

void CAnimationSequence2DInstance::Start()
{
	if (m_Owner && m_CurrentAnimation)
	{
		m_Owner->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, m_CurrentAnimation->m_Sequence->GetTexture()->GetName(), m_CurrentAnimation->m_Sequence->GetTexture());
	}
}

bool CAnimationSequence2DInstance::Init()
{
	if (m_Scene)
	{
		m_CBuffer = m_Scene->GetResource()->GetAnimation2DCBuffer();
	}

	return true;
}

void CAnimationSequence2DInstance::Update(float DeltaTime)
{
	if (!m_CurrentAnimation || !m_PlayAnimation || m_CurrentAnimation->m_Sequence->GetFrameCount() == 0)
	{
		return;
	}

	m_CurrentAnimation->m_Time += DeltaTime * m_CurrentAnimation->m_PlayScale;

	bool AnimEnd = false;

	m_CurrentAnimation->m_FrameTime = m_CurrentAnimation->m_PlayTime / m_CurrentAnimation->m_Sequence->GetFrameCount();

	if (m_CurrentAnimation->m_Time >= m_CurrentAnimation->m_FrameTime)
	{
		m_CurrentAnimation->m_Time -= m_CurrentAnimation->m_FrameTime;

		if (m_CurrentAnimation->m_Reverse)
		{
			m_CurrentAnimation->m_Frame--;

			if (m_CurrentAnimation->m_Frame < 0)
			{
				AnimEnd = true;
			}
		}

		else
		{
			m_CurrentAnimation->m_Frame++;

			if (m_CurrentAnimation->m_Frame == m_CurrentAnimation->m_Sequence->GetFrameCount())
			{
				AnimEnd = true;
			}
		}
	}

	// 호출해야 하는 Notify가 있는지 판단한다.
	size_t	Size = m_CurrentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < Size; i++)
	{
		if (!m_CurrentAnimation->m_vecNotify[i]->Call && m_CurrentAnimation->m_vecNotify[i]->Frame == m_CurrentAnimation->m_Frame)
		{
			m_CurrentAnimation->m_vecNotify[i]->Call = true;
			m_CurrentAnimation->m_vecNotify[i]->Function();
		}
	}

	if (AnimEnd)
	{
		if (m_CurrentAnimation->m_Loop)
		{
			if (m_CurrentAnimation->m_Reverse)
			{
				m_CurrentAnimation->m_Frame = m_CurrentAnimation->m_Sequence->GetFrameCount() - 1;
			}

			else
			{
				m_CurrentAnimation->m_Frame = 0;
			}
		}

		else
		{
			if (m_CurrentAnimation->m_Reverse)
			{
				m_CurrentAnimation->m_Frame = 0;
			}

			else
			{
				m_CurrentAnimation->m_Frame = m_CurrentAnimation->m_Sequence->GetFrameCount() - 1;
			}
		}

		if (m_CurrentAnimation->m_EndFunction)
		{
			m_CurrentAnimation->m_EndFunction();
		}

		if (m_CurrentAnimation->m_Loop)
		{
			size_t	Size = m_CurrentAnimation->m_vecNotify.size();

			for (size_t i = 0; i < Size; i++)
			{
				m_CurrentAnimation->m_vecNotify[i]->Call = false;
			}
		}
	}
}

void CAnimationSequence2DInstance::SetShader()
{
	if (!m_CurrentAnimation)
	{
		return;
	}

	else if (m_CurrentAnimation->m_Sequence->GetFrameCount() == 0)
	{
		return;
	}

	CAnimation2DConstantBuffer* Buffer = CResourceManager::GetInst()->GetAnimation2DCBuffer();

	const AnimationFrameData& FrameData = m_CurrentAnimation->m_Sequence->GetFrameData(m_CurrentAnimation->m_Frame);

	Image_Type Type = m_CurrentAnimation->m_Sequence->GetTexture()->GetImageType();

	Vector2	StartUV, EndUV;

	if (Type == Image_Type::Atlas)
	{
		Vector2	Start = m_CurrentAnimation->m_Sequence->GetFrameData(m_CurrentAnimation->m_Frame).Start;
		Vector2	FrameSize = m_CurrentAnimation->m_Sequence->GetFrameData(m_CurrentAnimation->m_Frame).Size;

		StartUV = Start / Vector2((float)m_CurrentAnimation->m_Sequence->GetTexture()->GetWidth(), (float)m_CurrentAnimation->m_Sequence->GetTexture()->GetHeight());

		EndUV = (Start + FrameSize) / Vector2((float)m_CurrentAnimation->m_Sequence->GetTexture()->GetWidth(), (float)m_CurrentAnimation->m_Sequence->GetTexture()->GetHeight());
	}

	else if (Type == Image_Type::Frame)
	{
		int Frame = m_CurrentAnimation->m_Frame;

		StartUV = Vector2(0.f, 0.f);

		EndUV = Vector2(1.f, 1.f);

		//m_CurrentAnimation->m_Sequence->GetTexture()->SetShader(0, (int)Buffer_Shader_Type::Pixel, Frame);

		if (m_Owner)
		{
			m_Owner->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, m_CurrentAnimation->m_Sequence->GetTexture()->GetName(), m_CurrentAnimation->m_Sequence->GetTexture());
			m_Owner->SetTextureFrameIndex(m_CurrentAnimation->m_Frame);
		}

		else
		{
			m_CurrentAnimation->m_Sequence->GetTexture()->SetShader(0, (int)Buffer_Shader_Type::Pixel, m_CurrentAnimation->m_Frame);
		}
	}

	/*else
	{
		Buffer->SetFrame(m_CurAnimation->m_Frame);
	}*/

	if (m_CBuffer)
	{
		m_CBuffer->SetAnimation2DType(Type);

		m_CBuffer->SetStartUV(StartUV);
		m_CBuffer->SetEndUV(EndUV);

		m_CBuffer->SetFlip(m_Flip);

		m_CBuffer->UpdateCBuffer();
	}
}

void CAnimationSequence2DInstance::ResetShader()
{
}

CAnimationSequence2DInstance* CAnimationSequence2DInstance::Clone()
{
	return new CAnimationSequence2DInstance(*this);
}

void CAnimationSequence2DInstance::Save(FILE* File)
{
	int	AnimCount = (int)m_mapAnimation.size();
	fwrite(&AnimCount, sizeof(int), 1, File);

	auto iter = m_mapAnimation.begin();
	auto iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		int	Length = (int)iter->first.length();
		fwrite(&Length, sizeof(int), 1, File);
		fwrite(iter->first.c_str(), sizeof(char), Length, File);

		iter->second->Save(File);
	}

	const std::string& CurrentName = m_CurrentAnimation->GetName();
	int	Length = (int)CurrentName.length();
	fwrite(&Length, sizeof(int), 1, File);
	fwrite(CurrentName.c_str(), sizeof(char), Length, File);

	fwrite(&m_PlayAnimation, sizeof(bool), 1, File);
}

void CAnimationSequence2DInstance::Load(FILE* File)
{
	int	AnimCount = 0;
	fread(&AnimCount, sizeof(int), 1, File);

	for (int i = 0; i < AnimCount; i++)
	{
		int	Length = 0;
		char AnimName[256] = {};

		fread(&Length, sizeof(int), 1, File);
		fread(AnimName, sizeof(char), Length, File);

		CAnimationSequence2DData* Data = new CAnimationSequence2DData;

		Data->Load(File);

		if (m_Scene)
		{
			Data->m_Sequence = m_Scene->GetResource()->FindAnimationSequence2D(Data->m_SequenceName);
		}

		else
		{
			Data->m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(Data->m_SequenceName);
		}

		m_mapAnimation.insert(std::make_pair(AnimName, Data));
	}

	int	Length = 0;
	char CurrentName[256] = {};

	fread(&Length, sizeof(int), 1, File);
	fread(CurrentName, sizeof(char), Length, File);

	m_CurrentAnimation = FindAnimation(CurrentName);

	fread(&m_PlayAnimation, sizeof(bool), 1, File);

	if (m_Scene)
	{
		m_CBuffer = m_Scene->GetResource()->GetAnimation2DCBuffer();
	}
}

CAnimationSequence2DData* CAnimationSequence2DInstance::FindAnimation(const std::string& Name)
{
	auto iter = m_mapAnimation.find(Name);

	if (iter == m_mapAnimation.end())
	{
		return nullptr;
	}

	return iter->second;
}