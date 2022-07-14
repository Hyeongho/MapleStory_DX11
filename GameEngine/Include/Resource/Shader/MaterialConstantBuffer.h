#pragma once

#include "ConstantBufferBase.h"

class CMaterialConstantBuffer :
    public CConstantBufferBase
{
public:
	CMaterialConstantBuffer();
	CMaterialConstantBuffer(const CMaterialConstantBuffer& Buffer);
	virtual ~CMaterialConstantBuffer();

protected:
	MaterialCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CMaterialConstantBuffer* Clone();

public:
	void SetBaseColor(const Vector4& BaseColor)
	{
		m_BufferData.BaseColor = BaseColor;
	}

	void SetOpacity(float Opacity)
	{
		m_BufferData.Opacity = Opacity;
	}

	void SetPaperBurn(bool Enable)
	{
		m_BufferData.PaperBurnEnable = Enable ? 1 : 0;
	}
};

