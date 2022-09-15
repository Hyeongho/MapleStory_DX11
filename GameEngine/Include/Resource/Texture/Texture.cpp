#include "Texture.h"
#include "../../PathManager.h"
#include "../../Device.h"

CTexture::CTexture() : m_Scene(nullptr), m_ImageType(Image_Type::Atlas), m_ArraySRV(nullptr)
{
}

CTexture::~CTexture()
{
	SAFE_RELEASE(m_ArraySRV);

	size_t Size = m_vecTextureInfo.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_vecTextureInfo[i]);
	}
}

bool CTexture::LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	TextureResourceInfo* Info = new TextureResourceInfo;

	SetName(Name);

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	TCHAR* FullPath = new TCHAR[MAX_PATH];
	memset(FullPath, 0, sizeof(TCHAR) * MAX_PATH);

	if (Path)
	{
		lstrcpy(FullPath, Path->Path);
	}

	lstrcat(FullPath, FileName);

	Info->FullPath = FullPath;

	Info->FileName = new TCHAR[MAX_PATH];
	memset(Info->FileName, 0, sizeof(TCHAR) * MAX_PATH);

	lstrcpy(Info->FileName, FileName);

	Info->PathName = new char[MAX_PATH];
	memset(Info->PathName, 0, sizeof(char) * MAX_PATH);

	strcpy_s(Info->PathName, PathName.length() + 1, PathName.c_str());

	char Ext[_MAX_EXT] = {};
	char FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	_splitpath_s(FullPathMultibyte, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

	_strupr_s(Ext);

	ScratchImage* Image = new ScratchImage;

	if (strcmp(Ext, ".DDS") == 0)
	{
		if (FAILED(LoadFromDDSFile(FullPath, DDS_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	else if (strcmp(Ext, ".TGA") == 0)
	{
		if (FAILED(LoadFromTGAFile(FullPath, nullptr, *Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	else
	{
		if (FAILED(LoadFromWICFile(FullPath, WIC_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	Info->Image = Image;

	m_vecTextureInfo.push_back(Info);

	return CreateResource(0);
}

bool CTexture::LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	TextureResourceInfo* Info = new TextureResourceInfo;

	SetName(Name);

	TCHAR* FullPath1 = new TCHAR[MAX_PATH];
	memset(FullPath1, 0, sizeof(TCHAR) * MAX_PATH);

	lstrcpy(FullPath1, FullPath);

	Info->FullPath = FullPath1;

	Info->FileName = new TCHAR[MAX_PATH];
	memset(Info->FileName, 0, sizeof(TCHAR) * MAX_PATH);

	int PathLength = lstrlen(Info->FullPath);

	// D:\Lecture\37th\API\GameFramework\GameFramework\Bin\Texture\Test.png
	for (int i = PathLength - 1; i > 0; --i)
	{
		if (Info->FullPath[i] == '\\' && i >= 4)
		{
			if ((Info->FullPath[i - 1] == 'n' || Info->FullPath[i - 1] == 'N') && 
				(Info->FullPath[i - 2] == 'i' || Info->FullPath[i - 2] == 'I') &&
				(Info->FullPath[i - 3] == 'b' || Info->FullPath[i - 3] == 'B') &&
				Info->FullPath[i - 4] == '\\')
			{
				lstrcpy(Info->FileName, &Info->FullPath[i + 1]);
				break;
			}
		}
	}

	TCHAR _FileExt[_MAX_EXT] = {};

	_wsplitpath_s(FullPath, nullptr, 0, nullptr, 0, nullptr, 0, _FileExt, _MAX_EXT);

	Info->PathName = new char[MAX_PATH];
	memset(Info->PathName, 0, sizeof(char) * MAX_PATH);

	strcpy_s(Info->PathName, strlen(ROOT_PATH) + 1, ROOT_PATH);

	char Ext[_MAX_EXT] = {};

#ifdef UNICODE

	int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, Ext, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(Ext, _FileExt);

#endif // UNICODE

	_strupr_s(Ext);

	ScratchImage* Image = new ScratchImage;

	if (strcmp(Ext, ".DDS") == 0)
	{
		if (FAILED(LoadFromDDSFile(FullPath, DDS_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	else if (strcmp(Ext, ".TGA") == 0)
	{
		if (FAILED(LoadFromTGAFile(FullPath, nullptr, *Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	else
	{
		if (FAILED(LoadFromWICFile(FullPath, WIC_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	Info->Image = Image;

	m_vecTextureInfo.push_back(Info);

	return CreateResource(0);
}

bool CTexture::LoadTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	m_ImageType = Image_Type::Frame;

	SetName(Name);

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	size_t Size = vecFileName.size();

	for (size_t i = 0; i < Size; i++)
	{
		TextureResourceInfo* Info = new TextureResourceInfo;

		TCHAR* FullPath = new TCHAR[MAX_PATH];
		memset(FullPath, 0, sizeof(TCHAR) * MAX_PATH);

		if (Path)
		{
			lstrcpy(FullPath, Path->Path);
		}

		lstrcat(FullPath, vecFileName[i]);

		Info->FullPath = FullPath;

		Info->FileName = new TCHAR[MAX_PATH];
		memset(Info->FileName, 0, sizeof(TCHAR) * MAX_PATH);

		lstrcpy(Info->FileName, vecFileName[i]);

		Info->PathName = new char[MAX_PATH];
		memset(Info->PathName, 0, sizeof(char) * MAX_PATH);

		strcpy_s(Info->PathName, PathName.length() + 1, PathName.c_str());

		char Ext[_MAX_EXT] = {};
		char FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

		int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

		strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

		_splitpath_s(FullPathMultibyte, nullptr, 0, nullptr, 0, nullptr, 0, Ext, _MAX_EXT);

		_strupr_s(Ext);

		ScratchImage* Image = new ScratchImage;

		if (strcmp(Ext, ".DDS") == 0)
		{
			if (FAILED(LoadFromDDSFile(FullPath, DDS_FLAGS_NONE, nullptr, *Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		else if (strcmp(Ext, ".TGA") == 0)
		{
			if (FAILED(LoadFromTGAFile(FullPath, nullptr, *Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		else
		{
			if (FAILED(LoadFromWICFile(FullPath, WIC_FLAGS_NONE, nullptr, *Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		Info->Image = Image;

		m_vecTextureInfo.push_back(Info);

		if (!CreateResource((int)i))
		{
			return false;
		}
	}

	//CreateResourceArray();

	return true;
}

bool CTexture::LoadTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	m_ImageType = Image_Type::Frame;

	SetName(Name);

	size_t Size = vecFullPath.size();

	for (size_t i = 0; i < Size; i++)
	{
		TextureResourceInfo* Info = new TextureResourceInfo;

		TCHAR* FullPath1 = new TCHAR[MAX_PATH];
		memset(FullPath1, 0, sizeof(TCHAR) * MAX_PATH);

		lstrcpy(FullPath1, vecFullPath[i]);

		Info->FullPath = FullPath1;

		Info->FileName = new TCHAR[MAX_PATH];
		memset(Info->FileName, 0, sizeof(TCHAR) * MAX_PATH);

		int PathLength = lstrlen(Info->FullPath);

		// D:\Lecture\37th\API\GameFramework\GameFramework\Bin\Texture\Test.png
		for (int i = PathLength - 1; i > 0; --i)
		{
			if (Info->FullPath[i] == '\\' && i >= 4)
			{
				if ((Info->FullPath[i - 1] == 'n' || Info->FullPath[i - 1] == 'N') &&
					(Info->FullPath[i - 2] == 'i' || Info->FullPath[i - 2] == 'I') &&
					(Info->FullPath[i - 3] == 'b' || Info->FullPath[i - 3] == 'B') &&
					Info->FullPath[i - 4] == '\\')
				{
					lstrcpy(Info->FileName, &Info->FullPath[i + 1]);
					break;
				}
			}
		}

		TCHAR _FileExt[_MAX_EXT] = {};

		_wsplitpath_s(vecFullPath[i], nullptr, 0, nullptr, 0, nullptr, 0, _FileExt, _MAX_EXT);

		Info->PathName = new char[MAX_PATH];
		memset(Info->PathName, 0, sizeof(char) * MAX_PATH);

		strcpy_s(Info->PathName, strlen(ROOT_PATH) + 1, ROOT_PATH);

		char Ext[_MAX_EXT] = {};

#ifdef UNICODE

		int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, nullptr, 0, nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, Ext, ConvertLength, nullptr, nullptr);

#else

		strcpy_s(Ext, _FileExt);

#endif // UNICODE

		_strupr_s(Ext);

		ScratchImage* Image = new ScratchImage;

		if (strcmp(Ext, ".DDS") == 0)
		{
			if (FAILED(LoadFromDDSFile(vecFullPath[i], DDS_FLAGS_NONE, nullptr, *Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		else if (strcmp(Ext, ".TGA") == 0)
		{
			if (FAILED(LoadFromTGAFile(vecFullPath[i], nullptr, *Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		else
		{
			if (FAILED(LoadFromWICFile(vecFullPath[i], WIC_FLAGS_NONE, nullptr, *Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		Info->Image = Image;

		m_vecTextureInfo.push_back(Info);

		if (!CreateResource((int)i))
		{
			return false;
		}
	}

	//CreateResourceArray();

	return true;
}

bool CTexture::CreateResource(int Index)
{
	if (FAILED(DirectX::CreateShaderResourceView(CDevice::GetInst()->GetDevice(), 
		m_vecTextureInfo[Index]->Image->GetImages(), 
		m_vecTextureInfo[Index]->Image->GetImageCount(),
		m_vecTextureInfo[Index]->Image->GetMetadata(), 
		&m_vecTextureInfo[Index]->SRV)))
	{
		return false;
	}

	m_vecTextureInfo[Index]->Width = (unsigned int)m_vecTextureInfo[Index]->Image->GetImages()[0].width;
	m_vecTextureInfo[Index]->Height = (unsigned int)m_vecTextureInfo[Index]->Image->GetImages()[0].height;

	return true;
}

bool CTexture::CreateResourceArray()
{
	ScratchImage* ArrayImage = new ScratchImage;

	size_t	MipLevel = m_vecTextureInfo[0]->Image->GetMetadata().mipLevels;
	size_t	Count = m_vecTextureInfo.size();

	if (FAILED(ArrayImage->Initialize2D(m_vecTextureInfo[0]->Image->GetMetadata().format, m_vecTextureInfo[0]->Image->GetMetadata().width,
		m_vecTextureInfo[0]->Image->GetMetadata().height, Count, MipLevel)))
	{
		return false;
	}

	for (size_t i = 0; i < Count; i++)
	{
		const Image* Images = m_vecTextureInfo[i]->Image->GetImages();

		MipLevel = m_vecTextureInfo[i]->Image->GetMetadata().mipLevels;

		for (size_t j = 0; j < MipLevel; j++)
		{
			const Image* Src = &ArrayImage->GetImages()[i * MipLevel + j];
			const Image* Dest = &Images[j];

			memcpy(Src->pixels, Dest->pixels, Src->slicePitch);
		}
	}

	ID3D11Texture2D* Tex = nullptr;

	if (FAILED(DirectX::CreateTextureEx(CDevice::GetInst()->GetDevice(), ArrayImage->GetImages(), ArrayImage->GetImageCount(), ArrayImage->GetMetadata(),
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false, (ID3D11Resource**)&Tex)))
	{
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC	Desc = {};
	Desc.Format = m_vecTextureInfo[0]->Image->GetMetadata().format;
	Desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	Desc.Texture2DArray.MostDetailedMip = 0;
	Desc.Texture2DArray.MipLevels = (UINT)m_vecTextureInfo[0]->Image->GetMetadata().mipLevels;
	Desc.Texture2DArray.FirstArraySlice = 0;
	Desc.Texture2DArray.ArraySize = (UINT)Count;


	if (FAILED(CDevice::GetInst()->GetDevice()->CreateShaderResourceView(Tex, &Desc, &m_ArraySRV)))
	{
		return false;
	}

	SAFE_DELETE(ArrayImage);

	SAFE_RELEASE(Tex);


	return true;
}

void CTexture::SetShader(int Register, int ShaderType, int Index)
{
	if (m_ImageType != Image_Type::Array)
	{
		if (ShaderType & (int)Buffer_Shader_Type::Vertex)
		{
			CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Pixel)
		{
			CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Domain)
		{
			CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Hull)
		{
			CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Geometry)
		{
			CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Compute)
		{
			CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);
		}
	}

	else
	{
		if (ShaderType & (int)Buffer_Shader_Type::Vertex)
		{
			CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &m_ArraySRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Pixel)
		{
			CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &m_ArraySRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Domain)
		{
			CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &m_ArraySRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Hull)
		{
			CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &m_ArraySRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Geometry)
		{
			CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &m_ArraySRV);
		}

		if (ShaderType & (int)Buffer_Shader_Type::Compute)
		{
			CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &m_ArraySRV);
		}
	}
}

void CTexture::ResetShader(int Register, int ShaderType, int Index)
{
	ID3D11ShaderResourceView* SRV = nullptr;

	if (ShaderType & (int)Buffer_Shader_Type::Vertex)
	{
		CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &SRV);
	}

	if (ShaderType & (int)Buffer_Shader_Type::Pixel)
	{
		CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &SRV);
	}

	if (ShaderType & (int)Buffer_Shader_Type::Domain)
	{
		CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &SRV);
	}

	if (ShaderType & (int)Buffer_Shader_Type::Hull)
	{
		CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &SRV);
	}

	if (ShaderType & (int)Buffer_Shader_Type::Geometry)
	{
		CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &SRV);
	}

	if (ShaderType & (int)Buffer_Shader_Type::Compute)
	{
		CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &SRV);
	}
}

void CTexture::Save(FILE* pFile)
{
	int	Length = (int)m_Name.length();
	fwrite(&Length, sizeof(int), 1, pFile);
	fwrite(m_Name.c_str(), sizeof(char), Length, pFile);

	fwrite(&m_ImageType, sizeof(Image_Type), 1, pFile);

	int	InfoCount = (int)m_vecTextureInfo.size();

	fwrite(&InfoCount, sizeof(int), 1, pFile);

	for (int i = 0; i < InfoCount; ++i)
	{
		int	PathSize = (int)lstrlen(m_vecTextureInfo[i]->FullPath);

		fwrite(&PathSize, sizeof(int), 1, pFile);
		fwrite(m_vecTextureInfo[i]->FullPath, sizeof(TCHAR), PathSize, pFile);

		PathSize = (int)lstrlen(m_vecTextureInfo[i]->FileName);

		fwrite(&PathSize, sizeof(int), 1, pFile);
		fwrite(m_vecTextureInfo[i]->FileName, sizeof(TCHAR), PathSize, pFile);
		
		PathSize = (int)strlen(m_vecTextureInfo[i]->PathName);

		fwrite(&PathSize, sizeof(int), 1, pFile);
		fwrite(m_vecTextureInfo[i]->PathName, sizeof(char), PathSize, pFile);
	}
}
