#include "BalrogRight.h"

CBalrogRight::CBalrogRight()
{
}

CBalrogRight::CBalrogRight(const CBalrogRight& obj)
{
}

CBalrogRight::~CBalrogRight()
{
}

void CBalrogRight::Start()
{
	CMonsterManager::Start();
}

bool CBalrogRight::Init()
{
	CMonsterManager::Init();

	InitAnimation();

	return true;
}

void CBalrogRight::Update(float DeltaTime)
{
	CObjectManager::Update(DeltaTime);
}

void CBalrogRight::PostUpdate(float DeltaTime)
{
	CObjectManager::PostUpdate(DeltaTime);
}

CBalrogRight* CBalrogRight::Clone()
{
	return new CBalrogRight(*this);
}

void CBalrogRight::InitAnimation()
{
}
