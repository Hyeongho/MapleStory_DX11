#include "BalrogLeft.h"

CBalrogLeft::CBalrogLeft()
{
}

CBalrogLeft::CBalrogLeft(const CBalrogLeft& obj)
{
}

CBalrogLeft::~CBalrogLeft()
{
}

void CBalrogLeft::Start()
{
	CMonsterManager::Start();
}

bool CBalrogLeft::Init()
{
	CMonsterManager::Init();

	InitAnimation();

	return true;
}

void CBalrogLeft::Update(float DeltaTime)
{
	CObjectManager::Update(DeltaTime);
}

void CBalrogLeft::PostUpdate(float DeltaTime)
{
	CObjectManager::PostUpdate(DeltaTime);
}

CBalrogLeft* CBalrogLeft::Clone()
{
	return new CBalrogLeft(*this);
}

void CBalrogLeft::InitAnimation()
{
}
