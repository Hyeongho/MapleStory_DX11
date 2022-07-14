#include "ParticleConstantBuffer.h"
#include "ConstantBuffer.h"

CParticleConstantBuffer::CParticleConstantBuffer() : m_BufferData{}
{
	m_BufferData.SpawnCountMax = 100;
	m_BufferData.ColorMin = Vector4(1.f, 1.f, 1.f, 1.f);
	m_BufferData.ColorMax = Vector4(1.f, 1.f, 1.f, 1.f);
	m_BufferData.LifeTimeMin = 0.5f;
	m_BufferData.LifeTimeMax = 1.f;
	m_BufferData.ScaleMin = Vector3(30.f, 30.f, 1.f);
	m_BufferData.ScaleMax = Vector3(30.f, 30.f, 1.f);
	m_BufferData.SpeedMin = 1.f;
	m_BufferData.SpeedMax = 3.f;
	m_BufferData.StartMin = Vector3(-10.f, -10.f, 0.f);
	m_BufferData.StartMax = Vector3(10.f, 10.f, 0.f);
}

CParticleConstantBuffer::CParticleConstantBuffer(const CParticleConstantBuffer& Buffer) : CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CParticleConstantBuffer::~CParticleConstantBuffer()
{
}

bool CParticleConstantBuffer::Init()
{
	SetConstantBuffer("ParticleCBuffer");

	return true;
}

void CParticleConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CParticleConstantBuffer* CParticleConstantBuffer::Clone()
{
	return new CParticleConstantBuffer(*this);
}
