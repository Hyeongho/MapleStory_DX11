#pragma once

#include "ConstantBufferBase.h"

class CGlobalConstantBuffer :
	public CConstantBufferBase
{
public:
	CGlobalConstantBuffer();
	CGlobalConstantBuffer(const CGlobalConstantBuffer& Buffer);
	virtual ~CGlobalConstantBuffer();

protected:
	GlobalCBuffer m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CGlobalConstantBuffer* Clone();

public:
	void SetDeltaTime(float Time)
	{
		m_BufferData.DeltaTime = Time;
	}

	void SetAccTime(float Time)
	{
		m_BufferData.AccTime = Time;
	}

	void SetResolution(const Resolution& RS)
	{
		m_BufferData.Resolution.x = (float)RS.Width;
		m_BufferData.Resolution.y = (float)RS.Height;
	}

	void SetNoiseResolution(float Width, float Height)
	{
		m_BufferData.NoiseResolution.x = Width;
		m_BufferData.NoiseResolution.y = Height;
	}
};

