#include "AnimationSequence2D.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../ResourceManager.h"
#include "../../PathManager.h"

CAnimationSequence2D::CAnimationSequence2D() : m_Scene(nullptr)
{
}

CAnimationSequence2D::~CAnimationSequence2D()
{
}

bool CAnimationSequence2D::Init(CTexture* Texture)
{
	m_Texture = Texture;

	return true;
}

bool CAnimationSequence2D::Init(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
		{
			return false;
		}

		m_Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		{
			return false;
		}

		m_Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	return true;
}

void CAnimationSequence2D::AddFrame(const Vector2& StartPos, const Vector2& Size)
{
	AnimationFrameData	Data = {};

	Data.Start = StartPos;
	Data.Size = Size;

	m_vecFrameData.push_back(Data);
}

void CAnimationSequence2D::AddFrame(float StartX, float StartY, float Width, float Height)
{
	AnimationFrameData	Data = {};

	Data.Start = Vector2(StartX, StartY);
	Data.Size = Vector2(Width, Height);

	m_vecFrameData.push_back(Data);
}

void CAnimationSequence2D::DeleteFrame(int Index)
{
	auto iter = m_vecFrameData.begin() + Index;

	m_vecFrameData.erase(iter);
}

void CAnimationSequence2D::ClearFrame()
{
	m_vecFrameData.clear();
}

bool CAnimationSequence2D::SaveFullPath(const char* FullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPath, "wb");

	if (!pFile)
	{
		return false;
	}

	int	Length = (int)m_Name.length();
	fwrite(&Length, sizeof(int), 1, pFile);
	fwrite(m_Name.c_str(), sizeof(char), Length, pFile);

	bool TexEnable = false;

	if (m_Texture)
	{
		TexEnable = true;
	}

	fwrite(&TexEnable, sizeof(bool), 1, pFile);

	if (m_Texture)
	{
		m_Texture->Save(pFile);
	}

	int	FrameCount = (int)m_vecFrameData.size();

	fwrite(&FrameCount, sizeof(int), 1, pFile);

	fwrite(&m_vecFrameData[0], sizeof(AnimationFrameData), FrameCount, pFile);

	fclose(pFile);

	return true;
}

bool CAnimationSequence2D::LoadFullPath(const char* FullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPath, "rb");

	if (!pFile)
	{
		return false;
	}

	int	Length = 0;
	fread(&Length, sizeof(int), 1, pFile);

	char Name[256] = {};
	fread(Name, sizeof(char), Length, pFile);
	m_Name = Name;

	bool TexEnable = false;

	fread(&TexEnable, sizeof(bool), 1, pFile);

	if (TexEnable)
	{
		int	TexNameLength = 0;
		fread(&TexNameLength, sizeof(int), 1, pFile);
		char TexName[256] = {};
		fread(TexName, sizeof(char), TexNameLength, pFile);

		Image_Type ImageType;
		fread(&ImageType, sizeof(Image_Type), 1, pFile);

		int	InfoCount = 0;

		fread(&InfoCount, sizeof(int), 1, pFile);

		std::vector<std::wstring>	vecFullPath;
		std::vector<std::wstring>	vecFileName;
		std::string	PathName;

		for (int i = 0; i < InfoCount; ++i)
		{
			int	PathSize = 0;

			fread(&PathSize, sizeof(int), 1, pFile);

			TCHAR FullPath[MAX_PATH] = {};
			fread(FullPath, sizeof(TCHAR), PathSize, pFile);
			vecFullPath.push_back(FullPath);

			fread(&PathSize, sizeof(int), 1, pFile);

			TCHAR TexFileName[MAX_PATH] = {};
			fread(TexFileName, sizeof(TCHAR), PathSize, pFile);
			vecFileName.push_back(TexFileName);

			fread(&PathSize, sizeof(int), 1, pFile);

			char TexPathName[MAX_PATH] = {};
			fread(TexPathName, sizeof(char), PathSize, pFile);

			PathName = TexPathName;
		}

		switch (ImageType)
		{
		case Image_Type::Atlas:
			if (vecFileName.size() == 1)
			{
				if (m_Scene)
				{
					m_Scene->GetResource()->LoadTexture(TexName, vecFileName[0].c_str(), PathName);
				}

				else
				{
					CResourceManager::GetInst()->LoadTexture(TexName, vecFileName[0].c_str(), PathName);
				}
			}

			else
			{
			}
			break;
		case Image_Type::Frame:
			if (vecFileName.size() == 1)
			{
			}

			else
			{
			}
			break;
		case Image_Type::Array:
			if (vecFileName.size() == 1)
			{
			}

			else
			{
			}
			break;
		}

		if (m_Scene)
		{
			m_Texture = m_Scene->GetResource()->FindTexture(TexName);
		}

		else
		{
			m_Texture = CResourceManager::GetInst()->FindTexture(TexName);
		}
	}

	int	FrameCount = 0;

	fread(&FrameCount, sizeof(int), 1, pFile);

	m_vecFrameData.resize((const size_t)FrameCount);

	fread(&m_vecFrameData[0], sizeof(AnimationFrameData), FrameCount, pFile);

	fclose(pFile);

	return true;
}

bool CAnimationSequence2D::Save(const char* FileName, const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	char FullPath[MAX_PATH] = {};

	if (Path)
	{
		strcpy_s(FullPath, Path->PathMultibyte);
	}

	strcat_s(FullPath, FileName);

	return SaveFullPath(FullPath);
}

bool CAnimationSequence2D::Load(const char* FileName, const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	char FullPath[MAX_PATH] = {};

	if (Path)
	{
		strcpy_s(FullPath, Path->PathMultibyte);
	}

	strcat_s(FullPath, FileName);

	return LoadFullPath(FullPath);
}
