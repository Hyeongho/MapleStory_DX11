#include "TileMapConstantBuffer.h"
#include "ConstantBuffer.h"

CTileMapConstantBuffer::CTileMapConstantBuffer() : m_BufferData{}
{
}

CTileMapConstantBuffer::CTileMapConstantBuffer(const CTileMapConstantBuffer& Buffer) : CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CTileMapConstantBuffer::~CTileMapConstantBuffer()
{
}

bool CTileMapConstantBuffer::Init()
{
	SetConstantBuffer("TileMapCBuffer");

	return true;
}

void CTileMapConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CTileMapConstantBuffer* CTileMapConstantBuffer::Clone()
{
	return new CTileMapConstantBuffer(*this);
}
