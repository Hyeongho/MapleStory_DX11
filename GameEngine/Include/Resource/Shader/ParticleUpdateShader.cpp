#include "ParticleUpdateShader.h"

CParticleUpdateShader::CParticleUpdateShader()
{
	SetTypeID<CParticleUpdateShader>();
}

CParticleUpdateShader::~CParticleUpdateShader()
{
}

bool CParticleUpdateShader::Init()
{
	if (!LoadComputeShader("ParticleUpdate", TEXT("Particle.fx"), SHADER_PATH))
	{
		return false;
	}

	return true;
}
