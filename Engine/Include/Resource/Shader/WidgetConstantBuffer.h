#pragma once

#include "ConstantBufferBase.h"

class CWidgetConstantBuffer :
    public CConstantBufferBase
{
public:
	CWidgetConstantBuffer();
	CWidgetConstantBuffer(const CWidgetConstantBuffer& Buffer);
	virtual ~CWidgetConstantBuffer();

protected:
	WidgetCBuffer m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CWidgetConstantBuffer* Clone();

public:
	void SetTint(const Vector4& Color)
	{
		m_BufferData.Tint = Color;
	}

	void SetWP(const Matrix& matWP)
	{
		m_BufferData.matWP = matWP;
	}

	void SetUseTexture(bool Use)
	{
		m_BufferData.UseTexture = Use ? 1 : 0;
	}

	void SetAnimType(int Type)
	{
		m_BufferData.WidgetAnimType = Type;
	}

	void SetStartUV(const Vector2& StartUV)
	{
		m_BufferData.WidgetAnimStartUV = StartUV;
	}

	void SetEndUV(const Vector2& EndUV)
	{
		m_BufferData.WidgetAnimEndUV = EndUV;
	}

	void SetAnimEnable(bool Enable)
	{
		m_BufferData.WidgetAnimEnable = Enable ? 1 : 0;
	}

	void SetOpacity(float Opacity)
	{
		m_BufferData.Opacity = Opacity;
	}
};

