#pragma once

#include "ConstantBufferBase.h"

class CColliderConstantBuffer :
	public CConstantBufferBase
{
public:
	CColliderConstantBuffer();
	CColliderConstantBuffer(const CColliderConstantBuffer& Buffer);
	virtual ~CColliderConstantBuffer();

protected:
	ColliderCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CColliderConstantBuffer* Clone();

public:
	void SetColliderColor(const Vector4& Color)
	{
		m_BufferData.Color = Color;
	}

	void SetWVP(const Matrix& matWVP)
	{
		m_BufferData.matWVP = matWVP;
	}
};

