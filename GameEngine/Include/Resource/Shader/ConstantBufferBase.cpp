#include "ConstantBufferBase.h"
#include "ConstantBuffer.h"
#include "../ResourceManager.h"

CConstantBufferBase::CConstantBufferBase()
{
}

CConstantBufferBase::CConstantBufferBase(const CConstantBufferBase& Buffer)
{
	m_Buffer = Buffer.m_Buffer;
}

CConstantBufferBase::~CConstantBufferBase()
{
}

void CConstantBufferBase::SetConstantBuffer(const std::string& Name)
{
	m_Buffer = CResourceManager::GetInst()->FindConstantBuffer(Name);
}
