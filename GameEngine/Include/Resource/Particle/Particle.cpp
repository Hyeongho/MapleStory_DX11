#include "Particle.h"
#include "../Shader/StructuredBuffer.h"
#include "../Shader/ShaderManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../ResourceManager.h"

CParticle::CParticle() : m_CBuffer(nullptr), m_SpawnTime(0.001f), m_2D(true), m_SpawnCountMax(100)
{
}

CParticle::CParticle(const CParticle& particle)
{
	m_CBuffer = particle.m_CBuffer->Clone();
	m_UpdateShader = particle.m_UpdateShader;
}

CParticle::~CParticle()
{
	size_t BufferCount = m_vecStructuredBuffer.size();

	for (size_t i = 0; i < BufferCount; i++)
	{
		SAFE_DELETE(m_vecStructuredBuffer[i]);
	}

	SAFE_DELETE(m_CBuffer);
}

bool CParticle::Init()
{
	m_CBuffer = new CParticleConstantBuffer;

	if (!m_CBuffer->Init())
	{
		return false;
	}

	if (m_Scene)
	{
		m_UpdateShader = (CParticleUpdateShader*)m_Scene->GetResource()->FindShader("ParticleUpdateShader");
	}

	else
	{
		m_UpdateShader = (CParticleUpdateShader*)CResourceManager::GetInst()->FindShader("ParticleUpdateShader");
	}

	AddStructuredBuffer("ParticleInfo", sizeof(ParticleInfo), m_SpawnCountMax, 0);
	AddStructuredBuffer("ParticleInfoShared", sizeof(ParticleInfoShared), 1, 1);

	return true;
}

void CParticle::AddStructuredBuffer(const std::string& Name, unsigned int Size, unsigned int Count, 
	int Register, bool Dynamic, int StructuredBufferShaderType)
{
	CStructuredBuffer* Buffer = new CStructuredBuffer;

	if (!Buffer->Init(Name, Size, Count, Register, Dynamic, StructuredBufferShaderType))
	{
		SAFE_DELETE(Buffer);
		return;
	}

	m_vecStructuredBuffer.push_back(Buffer);

}

bool CParticle::ResizeBuffer(const std::string& Name, unsigned int Size, unsigned int Count,
	int Register, bool Dynamic, int StructuredBufferShaderType)
{
	size_t	BufferCount = m_vecStructuredBuffer.size();

	for (size_t i = 0; i < BufferCount; ++i)
	{
		if (m_vecStructuredBuffer[i]->GetName() == Name)
		{
			m_vecStructuredBuffer[i]->Init(Name, Size, Count, Register, Dynamic, StructuredBufferShaderType);

			return true;
		}
	}

	return false;
}

void CParticle::CloneStructuredBuffer(std::vector<CStructuredBuffer*>& vecBuffer)
{
	size_t	BufferCount = m_vecStructuredBuffer.size();

	for (size_t i = 0; i < BufferCount; ++i)
	{
		CStructuredBuffer* Buffer = m_vecStructuredBuffer[i]->Clone();

		vecBuffer.push_back(Buffer);
	}
}

void CParticle::SetSpawnCountMax(unsigned int Count)
{
	m_CBuffer->SetSpawnCountMax(Count);

	m_SpawnCountMax = Count;

	ResizeBuffer("ParticleInfo", sizeof(ParticleInfo), m_SpawnCountMax, 0);
}
