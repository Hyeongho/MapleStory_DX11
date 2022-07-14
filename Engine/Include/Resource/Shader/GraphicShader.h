#pragma once
#include "Shader.h"
class CGraphicShader :
	public CShader
{
	friend class CShaderManager;

protected:
	CGraphicShader();
	CGraphicShader(const CGraphicShader& shader);
	virtual ~CGraphicShader() = 0;

private:
	ID3D11InputLayout* m_InputLayout;
	std::vector<D3D11_INPUT_ELEMENT_DESC>   m_vecInputDesc;
	unsigned int        m_InputSize;

private:
	ID3D11VertexShader* m_VS;
	ID3DBlob* m_VSBlob;

	ID3D11PixelShader* m_PS;
	ID3DBlob* m_PSBlob;

	ID3D11HullShader* m_HS;
	ID3DBlob* m_HSBlob;

	ID3D11DomainShader* m_DS;
	ID3DBlob* m_DSBlob;

	ID3D11GeometryShader* m_GS;
	ID3DBlob* m_GSBlob;

public:
	void AddInputDesc(const char* Name, unsigned int Index, DXGI_FORMAT Fmt, unsigned int Slot, unsigned int Size, D3D11_INPUT_CLASSIFICATION SlotClass, unsigned int InstanceDataStep);
	bool CreateInputLayout();

public:
	virtual bool Init() = 0;
	virtual void SetShader();
	virtual CGraphicShader* Clone();

public:
	bool LoadVertexShader(const char* EntryName, const TCHAR* FileName, const std::string& PathName);
	bool LoadPixelShader(const char* EntryName, const TCHAR* FileName, const std::string& PathName);
	bool LoadHullShader(const char* EntryName, const TCHAR* FileName, const std::string& PathName);
	bool LoadDomainShader(const char* EntryName, const TCHAR* FileName, const std::string& PathName);
	bool LoadGeometryShader(const char* EntryName, const TCHAR* FileName, const std::string& PathName);
};

