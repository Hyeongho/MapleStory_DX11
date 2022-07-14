#include "ProgressBarConstantBuffer.h"
#include "ConstantBuffer.h"

CProgressBarConstantBuffer::CProgressBarConstantBuffer() : m_BufferData{}
{
}

CProgressBarConstantBuffer::CProgressBarConstantBuffer(const CProgressBarConstantBuffer& Buffer) : CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CProgressBarConstantBuffer::~CProgressBarConstantBuffer()
{
}

bool CProgressBarConstantBuffer::Init()
{
	SetConstantBuffer("ProgressBarCBuffer");

	return true;
}

void CProgressBarConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CProgressBarConstantBuffer* CProgressBarConstantBuffer::Clone()
{
	return new CProgressBarConstantBuffer(*this);
}
