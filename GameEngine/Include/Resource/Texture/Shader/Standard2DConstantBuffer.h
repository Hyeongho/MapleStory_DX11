#pragma once

#include "ConstantBufferBase.h"

class CStandard2DConstantBuffer :
    public CConstantBufferBase
{
public:
	CStandard2DConstantBuffer();
	CStandard2DConstantBuffer(const CStandard2DConstantBuffer& Buffer);
	virtual ~CStandard2DConstantBuffer();

protected:
	Standard2DCBuffer m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CStandard2DConstantBuffer* Clone();

public:
	void SetAnimation2DEnable(bool Enable)
	{
		m_BufferData.AnimationEnable = Enable ? 1 : 0;
	}
};

