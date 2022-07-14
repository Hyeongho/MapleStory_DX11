#include "WidgetConstantBuffer.h"
#include "ConstantBuffer.h"

CWidgetConstantBuffer::CWidgetConstantBuffer() : m_BufferData{}
{
	m_BufferData.Tint = Vector4(1.f, 1.f, 1.f, 1.f);
	m_BufferData.Opacity = 1.f;
}

CWidgetConstantBuffer::CWidgetConstantBuffer(const CWidgetConstantBuffer& Buffer) : CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CWidgetConstantBuffer::~CWidgetConstantBuffer()
{
}

bool CWidgetConstantBuffer::Init()
{
	SetConstantBuffer("WidgetCBuffer");

	return true;
}

void CWidgetConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CWidgetConstantBuffer* CWidgetConstantBuffer::Clone()
{
	return new CWidgetConstantBuffer(*this);
}