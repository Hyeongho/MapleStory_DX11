#include "Material.h"
#include "../ResourceManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../../Render/RenderManager.h"
#include "../../Render/RenderState.h"

CMaterial::CMaterial() : m_BaseColor(Vector4::White), m_Scene(nullptr), m_CBuffer(nullptr), m_Opacity(1.f), m_Flip(true), m_RenderStateArray{}
{
	SetTypeID<CMaterial>();
}

CMaterial::CMaterial(const CMaterial& Material)
{
	*this = Material;

	m_RefCount = 0;

	m_CBuffer = Material.m_CBuffer->Clone();

	m_Scene = nullptr;

	m_RenderCallback.clear();
}

CMaterial::~CMaterial()
{
	auto iter = m_RenderCallback.begin();
	auto iterEnd = m_RenderCallback.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE((*iter));
	}

	SAFE_DELETE(m_CBuffer);
}

void CMaterial::SetRenderState(CRenderState* State)
{
	m_RenderStateArray[(int)RenderState_Type::Blend] = State;
}

void CMaterial::SetRenderState(const std::string& Name)
{
	m_RenderStateArray[(int)RenderState_Type::Blend] = CRenderManager::GetInst()->FindRenderState(Name);
}

void CMaterial::SetTransparency(bool Enable)
{
	if (Enable)
	{
		m_RenderStateArray[(int)RenderState_Type::Blend] = CRenderManager::GetInst()->FindRenderState("AlphaBlend");
	}
}

void CMaterial::SetOpacity(float Opacity)
{
	m_Opacity = Opacity;

	if (m_Opacity < 0.f)
	{
		m_Opacity = 0.f;
	}

	else if (m_Opacity > 1.f)
	{
		m_Opacity = 1.f;
	}
}

void CMaterial::AddOpacity(float Opacity)
{
	m_Opacity += Opacity;

	if (m_Opacity < 0.f)
	{
		m_Opacity = 0.f;
	}

	else if (m_Opacity > 1.f)
	{
		m_Opacity = 1.f;
	}
}

void CMaterial::SetBaseColor(const Vector4& Color)
{
	m_BaseColor = Color;
}

void CMaterial::SetBaseColor(float r, float g, float b, float a)
{
	m_BaseColor = Vector4(r, g, b, a);
}

void CMaterial::AddTexture(int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = Texture;
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::AddTexture(int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CTexture* Texture = nullptr;

	if (!m_Scene)
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		{
			return;
		}

		Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	else
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
		{
			return;
		}

		Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = Texture;
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::AddTextureFullPath(int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	/*if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;*/
}

void CMaterial::AddTexture(int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	/*if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo.push_back(MaterialTextureInfo());

	int	Index = (int)m_TextureInfo.size() - 1;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;*/
}

void CMaterial::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, CTexture* Texture)
{
	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = Texture;
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CTexture* Texture = nullptr;

	if (!m_Scene)
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		{
			return;
		}

		Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	else
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
		{
			return;
		}

		Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = Texture;
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::SetTextureFullPath(int Index, int Register, int ShaderType, const std::string& Name, const TCHAR* FullPath)
{
	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
	{
		return;
	}

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;
}

void CMaterial::SetTexture(int Index, int Register, int ShaderType, const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	/*if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return;

	m_TextureInfo[Index].Register = Register;
	m_TextureInfo[Index].Name = Name;
	m_TextureInfo[Index].Texture = CResourceManager::GetInst()->FindTexture(Name);
	m_TextureInfo[Index].ShaderType = ShaderType;*/
}

void CMaterial::SetPaperBurn(bool Enable)
{
	m_CBuffer->SetPaperBurn(Enable);
}

void CMaterial::SetShader(const std::string& Name)
{
	m_Shader = (CGraphicShader*)CResourceManager::GetInst()->FindShader(Name);
}

void CMaterial::Render()
{
	if (m_Shader)
	{
		m_Shader->SetShader();
	}

	if (m_CBuffer)
	{
		m_CBuffer->SetBaseColor(m_BaseColor);
		m_CBuffer->SetOpacity(m_Opacity);

		m_CBuffer->UpdateCBuffer();
	}

	for (int i = 0; i < (int)RenderState_Type::Max; ++i)
	{
		if (m_RenderStateArray[i])
		{
			m_RenderStateArray[i]->SetState();
		}
	}

	size_t Size = m_TextureInfo.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_TextureInfo[i].Texture->SetShader(m_TextureInfo[i].Register, m_TextureInfo[i].ShaderType, 0);
	}

	auto iter = m_RenderCallback.begin();
	auto iterEnd = m_RenderCallback.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Func();
	}
}

void CMaterial::Reset()
{
	size_t	Size = m_TextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_TextureInfo[i].Texture->ResetShader(m_TextureInfo[i].Register, m_TextureInfo[i].ShaderType, 0);
	}

	for (int i = 0; i < (int)RenderState_Type::Max; ++i)
	{
		if (m_RenderStateArray[i])
		{
			m_RenderStateArray[i]->ResetState();
		}
	}
}

CMaterial* CMaterial::Clone()
{
	return new CMaterial(*this);
}

void CMaterial::Save(FILE* File)
{
	std::string	ShaderName = m_Shader->GetName();

	int	Length = (int)ShaderName.length();

	fwrite(&Length, sizeof(int), 1, File);
	fwrite(ShaderName.c_str(), sizeof(char), Length, File);

	fwrite(&m_BaseColor, sizeof(Vector4), 1, File);
	fwrite(&m_Opacity, sizeof(float), 1, File);

	for (int i = 0; i < (int)RenderState_Type::Max; ++i)
	{
		bool StateEnable = false;

		if (m_RenderStateArray[i])
		{
			StateEnable = true;
		}

		fwrite(&StateEnable, sizeof(bool), 1, File);

		if (m_RenderStateArray[i])
		{
			std::string	StateName = m_RenderStateArray[i]->GetName();

			int	Length = (int)StateName.length();

			fwrite(&Length, sizeof(int), 1, File);
			fwrite(StateName.c_str(), sizeof(char), Length, File);
		}
	}

	int	TextureCount = (int)m_TextureInfo.size();

	fwrite(&TextureCount, sizeof(int), 1, File);

	for (int i = 0; i < TextureCount; ++i)
	{
		int	Length = (int)m_TextureInfo[i].Name.length();

		fwrite(&Length, sizeof(int), 1, File);
		fwrite(m_TextureInfo[i].Name.c_str(), sizeof(char), Length, File);

		fwrite(&m_TextureInfo[i].SamplerType, sizeof(Sampler_Type), 1, File);
		fwrite(&m_TextureInfo[i].Register, sizeof(int), 1, File);
		fwrite(&m_TextureInfo[i].ShaderType, sizeof(int), 1, File);

		m_TextureInfo[i].Texture->Save(File);
	}
}

void CMaterial::Load(FILE* File)
{
	char	ShaderName[256] = {};

	int	Length = 0;

	fread(&Length, sizeof(int), 1, File);
	fread(ShaderName, sizeof(char), Length, File);

	m_Shader = (CGraphicShader*)CResourceManager::GetInst()->FindShader(ShaderName);

	fread(&m_BaseColor, sizeof(Vector4), 1, File);
	fread(&m_Opacity, sizeof(float), 1, File);

	for (int i = 0; i < (int)RenderState_Type::Max; ++i)
	{
		bool	StateEnable = false;

		fread(&StateEnable, sizeof(bool), 1, File);

		if (StateEnable)
		{
			char	StateName[256] = {};
			Length = 0;

			fread(&Length, sizeof(int), 1, File);
			fread(StateName, sizeof(char), Length, File);

			m_RenderStateArray[i] = CRenderManager::GetInst()->FindRenderState(StateName);
		}
	}

	int	TextureCount = 0;

	fread(&TextureCount, sizeof(int), 1, File);

	for (int i = 0; i < TextureCount; ++i)
	{
		m_TextureInfo.push_back(MaterialTextureInfo());

		Length = 0;

		char TextureName[256] = {};

		fread(&Length, sizeof(int), 1, File);
		fread(TextureName, sizeof(char), Length, File);

		m_TextureInfo[i].Name = TextureName;

		fread(&m_TextureInfo[i].SamplerType, sizeof(Sampler_Type), 1, File);
		fread(&m_TextureInfo[i].Register, sizeof(int), 1, File);
		fread(&m_TextureInfo[i].ShaderType, sizeof(int), 1, File);

		int TexNameLength = 0;
		fread(&TexNameLength, sizeof(int), 1, File);
		char TexName[256] = {};
		fread(TexName, sizeof(char), TexNameLength, File);

		Image_Type	ImageType;
		fread(&ImageType, sizeof(Image_Type), 1, File);

		int	InfoCount = 0;

		fread(&InfoCount, sizeof(int), 1, File);

		std::vector<std::wstring>	vecFullPath;
		std::vector<std::wstring>	vecFileName;
		std::string	PathName;

		for (int i = 0; i < InfoCount; i++)
		{
			int	PathSize = 0;

			fread(&PathSize, sizeof(int), 1, File);

			TCHAR FullPath[MAX_PATH] = {};
			fread(FullPath, sizeof(TCHAR), PathSize, File);
			vecFullPath.push_back(FullPath);

			fread(&PathSize, sizeof(int), 1, File);

			TCHAR TexFileName[MAX_PATH] = {};
			fread(TexFileName, sizeof(TCHAR), PathSize, File);
			vecFileName.push_back(TexFileName);

			fread(&PathSize, sizeof(int), 1, File);

			char TexPathName[MAX_PATH] = {};
			fread(TexPathName, sizeof(char), PathSize, File);

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
			m_TextureInfo[i].Texture = m_Scene->GetResource()->FindTexture(TexName);
		}

		else
		{
			m_TextureInfo[i].Texture = CResourceManager::GetInst()->FindTexture(TexName);
		}
	}
}
