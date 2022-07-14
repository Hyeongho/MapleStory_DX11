#pragma once

#include "ConstantBufferBase.h"

class CAnimation2DConstantBuffer :
    public CConstantBufferBase
{
public:
	CAnimation2DConstantBuffer();
	CAnimation2DConstantBuffer(const CAnimation2DConstantBuffer& Buffer);
	virtual ~CAnimation2DConstantBuffer();

protected:
	Animation2DCBuffer m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CAnimation2DConstantBuffer* Clone();

public:
	void SetAnimation2DType(Image_Type Type)
	{
		m_BufferData.Animation2DType = (int)Type;
	}

	void SetStartUV(const Vector2& StartUV)
	{
		m_BufferData.Animation2DStartUV = StartUV;
	}

	void SetEndUV(const Vector2& EndUV)
	{
		m_BufferData.Animation2DEndUV = EndUV;
	}

	void SetFlip(bool Flip)
	{
		m_BufferData.AnimFlip = Flip ? 1 : 0;
	}
};

