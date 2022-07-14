#pragma once

#include "../../GameInfo.h"

class CStructuredBuffer
{
public:
	CStructuredBuffer();
	CStructuredBuffer(const CStructuredBuffer& buffer);
	~CStructuredBuffer();

private:
	std::string	 m_Name;
	D3D11_BUFFER_DESC m_Desc;
	ID3D11Buffer* m_Buffer;

	ID3D11ShaderResourceView* m_SRV;
	ID3D11UnorderedAccessView* m_UAV;

	unsigned int m_Size;
	unsigned int m_Count;
	int m_StructuredBufferShaderType;
	int m_Register;
	bool m_Dynamic;

public:
	ID3D11Buffer* GetBuffer() const
	{
		return m_Buffer;
	}

	const std::string& GetName() const
	{
		return m_Name;
	}

public:
	bool Init(const std::string& Name, unsigned int Size, unsigned int Count, int Register, bool Dynamic = false,
		int StructuredBufferShaderType = (int)Buffer_Shader_Type::Compute);
	void UpdateBuffer(void* Data, int Count);
	CStructuredBuffer* Clone();
	void SetShader();
	void ResetShader();
	void SetShader(int Register, int StructuredBufferShaderType);
	void ResetShader(int Register, int StructuredBufferShaderType);
	void CopyData(void* Data);
	void CopyResource(CStructuredBuffer* Buffer);
};

