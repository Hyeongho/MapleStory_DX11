#include "TestMonster.h"
#include "Scene/Scene.h"

CTestMonster::CTestMonster()
{
	SetTypeID<CTestMonster>();

	m_SolW = false;
	m_WDistance = 0.f;
	m_Opacity = 1.f;
}

CTestMonster::CTestMonster(const CTestMonster& obj) : CMonsterManager(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("TestMonsterSprite");

	m_Body = (CColliderBox2D*)FindComponent("Body");

	//m_Sensor = (CColliderBox2D*)FindComponent("Sensor");

	m_Opacity = obj.m_Opacity;
}

CTestMonster::~CTestMonster()
{
}

void CTestMonster::Start()
{
	CMonsterManager::Start();
}

bool CTestMonster::Init()
{
	CMonsterManager::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("TestMonsterSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	//m_Sensor = CreateComponent<CColliderBox2D>("Sensor");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	//m_Sensor->AddCollisionCallback<CTestMonster>(Collision_State::Begin, this, &CTestMonster::CollisionCallback);
	m_Body->AddCollisionCallback<CTestMonster>(Collision_State::Begin, this, &CTestMonster::CollisionCallback);

	m_Sprite->AddChild(m_Body);
	//m_Sprite->AddChild(m_Sensor);

	m_Sprite->SetTransparency(true);

	m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 1000.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->SetExtent(300.f, 100.f);

	SetGravityAccel(30.f);
	SetPhysicsSimulate(false);
	SetJumpVelocity(40.f);
	SetSideWallCheck(false);

	return true;
}

void CTestMonster::Update(float DeltaTime)
{
	CMonsterManager::Update(DeltaTime);
}

void CTestMonster::PostUpdate(float DeltaTime)
{
	CMonsterManager::PostUpdate(DeltaTime);
}

CTestMonster* CTestMonster::Clone()
{
	return new CTestMonster(*this);
}

void CTestMonster::CollisionCallback(const CollisionResult& result)
{
	result.Src->GetCollisionProfile();

	if (result.Dest->GetCollisionProfile()->Name == "Player")
	{
		MessageBox(0, TEXT("Click"), TEXT("Click"), MB_OK);
	}
}
