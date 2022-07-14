#include "GlobalConstantBuffer.h"
#include "ConstantBuffer.h"

CGlobalConstantBuffer::CGlobalConstantBuffer() : m_BufferData{}
{
}

CGlobalConstantBuffer::CGlobalConstantBuffer(const CGlobalConstantBuffer& Buffer) : CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CGlobalConstantBuffer::~CGlobalConstantBuffer()
{
}

bool CGlobalConstantBuffer::Init()
{
	SetConstantBuffer("GlobalCBuffer");

	return true;
}

void CGlobalConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CGlobalConstantBuffer* CGlobalConstantBuffer::Clone()
{
	return new CGlobalConstantBuffer(*this);
}
