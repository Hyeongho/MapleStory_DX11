#pragma once
#include "ConstantBufferBase.h"
class CPaperBurnConstantBuffer :
    public CConstantBufferBase
{
public:
	CPaperBurnConstantBuffer();
	CPaperBurnConstantBuffer(const CPaperBurnConstantBuffer& Buffer);
	virtual ~CPaperBurnConstantBuffer();

protected:
	PaperBurnCBuffer m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CPaperBurnConstantBuffer* Clone();

public:
	void SetInColor(const Vector4& Color)
	{
		m_BufferData.InLineColor = Color;
	}

	void SetInColor(float r, float g, float b, float a)
	{
		m_BufferData.InLineColor = Vector4(r, g, b, a);
	}

	void SetOutColor(const Vector4& Color)
	{
		m_BufferData.OutLineColor = Color;
	}

	void SetOutColor(float r, float g, float b, float a)
	{
		m_BufferData.OutLineColor = Vector4(r, g, b, a);
	}

	void SetCenterColor(const Vector4& Color)
	{
		m_BufferData.CenterLineColor = Color;
	}

	void SetCenterColor(float r, float g, float b, float a)
	{
		m_BufferData.CenterLineColor = Vector4(r, g, b, a);
	}

	void SetFilter(float Filter)
	{
		m_BufferData.Filter = Filter;
	}

	void AddFilter(float Filter)
	{
		m_BufferData.Filter += Filter;
	}

	void SetInverse(bool Inverse)
	{
		m_BufferData.Inverse = Inverse ? 1 : 0;
	}

	void SetInFilter(float Filter)
	{
		m_BufferData.InFilter = Filter;
	}

	void SetOutFilter(float Filter)
	{
		m_BufferData.OutFilter = Filter;
	}

	void SetCenterFilter(float Filter)
	{
		m_BufferData.CenterFilter = Filter;
	}
};

