#include "Animation2DConstantBuffer.h"
#include "ConstantBuffer.h"

CAnimation2DConstantBuffer::CAnimation2DConstantBuffer() : m_BufferData{}
{
}

CAnimation2DConstantBuffer::CAnimation2DConstantBuffer(const CAnimation2DConstantBuffer& Buffer) : CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CAnimation2DConstantBuffer::~CAnimation2DConstantBuffer()
{
}

bool CAnimation2DConstantBuffer::Init()
{
	SetConstantBuffer("Animation2DCBuffer");

	return true;
}

void CAnimation2DConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CAnimation2DConstantBuffer* CAnimation2DConstantBuffer::Clone()
{
	return new CAnimation2DConstantBuffer(*this);
}
