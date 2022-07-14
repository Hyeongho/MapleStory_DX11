#include "TransformConstantBuffer.h"
#include "ConstantBuffer.h"

CTransformConstantBuffer::CTransformConstantBuffer() : m_BufferData{}
{
}

CTransformConstantBuffer::CTransformConstantBuffer(const CTransformConstantBuffer& Buffer) : CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CTransformConstantBuffer::~CTransformConstantBuffer()
{
}

bool CTransformConstantBuffer::Init()
{
	SetConstantBuffer("TransformCBuffer");

	return true;
}

void CTransformConstantBuffer::UpdateCBuffer()
{
	m_BufferData.matWV = m_BufferData.matWorld * m_BufferData.matView;
	m_BufferData.matWVP = m_BufferData.matWV * m_BufferData.matProj;
	m_BufferData.matVP = m_BufferData.matView * m_BufferData.matProj;

	// Shader���� ����� �� �ְ� �ϱ� ���ؼ��� ���⿡���� ����� ��ġ���־ �Ѱ��־�� �Ѵ�.
	m_BufferData.matWorld.Transpose();
	m_BufferData.matView.Transpose();
	m_BufferData.matProj.Transpose();
	m_BufferData.matWV.Transpose();
	m_BufferData.matWVP.Transpose();
	m_BufferData.matVP.Transpose();

	m_Buffer->UpdateBuffer(&m_BufferData);
}

CTransformConstantBuffer* CTransformConstantBuffer::Clone()
{
	return new CTransformConstantBuffer(*this);
}
