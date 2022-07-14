#pragma once

#include "ConstantBufferBase.h"

class CProgressBarConstantBuffer :
	public CConstantBufferBase
{
public:
	CProgressBarConstantBuffer();
	CProgressBarConstantBuffer(const CProgressBarConstantBuffer& Buffer);
	virtual ~CProgressBarConstantBuffer();

protected:
	ProgressBarCBuffer m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CProgressBarConstantBuffer* Clone();

public:
	void SetPercent(float Percent)
	{
		m_BufferData.Percent = Percent;
	}

	void SetDir(ProgressBar_Dir Dir)
	{
		m_BufferData.Dir = (int)Dir;
	}
};

