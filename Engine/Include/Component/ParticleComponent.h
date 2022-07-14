#pragma once

#include "SceneComponent.h"
#include "../Resource/Particle/Particle.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/ParticleUpdateShader.h"
#include "../Resource/Shader/ParticleRenderShader.h"
#include "../Resource/Shader/ParticleConstantBuffer.h"
#include "../Resource/Material/Material.h"

class CParticleComponent :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CParticleComponent();
	CParticleComponent(const CParticleComponent& com);
	virtual ~CParticleComponent();

protected:
	CSharedPtr<CParticle> m_Particle;
	std::vector<class CStructuredBuffer*> m_vecStructuredBuffer;
	CSharedPtr<CMesh> m_Mesh;
	CSharedPtr<CMaterial> m_Material;
	CSharedPtr<CParticleUpdateShader> m_UpdateShader;
	CParticleConstantBuffer* m_CBuffer;
	ParticleInfo m_Info;
	ParticleInfoShared m_InfoShared;
	float m_SpawnTime;
	float m_SpawnTimeMax;

public:
	void SetParticle(const std::string& Name);
	void SetParticle(CParticle* Particle);
	void SetSpawnTime(float Time);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CParticleComponent* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

