#pragma once

#include "../../GameInfo.h"

class CTextureManager
{
	friend class CResourceManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CTexture>>	m_mapTexture;
	std::unordered_map<std::string, ID3D11SamplerState*> m_mapSampler;

public:
	bool Init();

	bool LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	bool LoadTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
	bool LoadTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName, const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath);
	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);

public:
	/*
	D3D11_FILTER Filter;
    D3D11_TEXTURE_ADDRESS_MODE AddressU;
    D3D11_TEXTURE_ADDRESS_MODE AddressV;
    D3D11_TEXTURE_ADDRESS_MODE AddressW;
    FLOAT MipLODBias;
    UINT MaxAnisotropy;
    D3D11_COMPARISON_FUNC ComparisonFunc;
    FLOAT BorderColor[ 4 ];
    FLOAT MinLOD;
    FLOAT MaxLOD;
	*/
	bool CreateSampler(const std::string& Name, D3D11_FILTER Filter,
		D3D11_TEXTURE_ADDRESS_MODE AddressU,
		D3D11_TEXTURE_ADDRESS_MODE AddressV,
		D3D11_TEXTURE_ADDRESS_MODE AddressW,
		float BorderColor[4]);
	ID3D11SamplerState* FindSampler(const std::string& Name);
	void SetSampler(const std::string& Name, int Register, int ShaderType = (int)Buffer_Shader_Type::All);
};

