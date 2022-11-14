#include "BalrogLeft.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"
#include "Input.h"

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

	//InitAnimation();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogLeft");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");

	m_Sprite->SetLayerName("BalrogHand");

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(1000.f, 1000.f, 1.f);

	m_Sprite->GetWorldPos();
	m_Sprite->GetWorldScale();

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation("BalrogLeftIdle", "BalrogLeftIdle", true, 2.04f);
	m_Anim->AddAnimation("BalrogLeftDie", "BalrogLeftDie", false, 3.36f);
	m_Anim->AddAnimation("BalrogLeftAttack1", "BalrogLeftAttack1", false, 2.1f);
	m_Anim->AddAnimation("BalrogLeftAttack2", "BalrogLeftAttack2", false, 3.48f);

	m_Anim->SetCurrentAnimation("BalrogLeftIdle");

	m_Anim->SetEndFunction<CBalrogLeft>("BalrogLeftAttack1", this, &CBalrogLeft::AnimationFinish);
	m_Anim->SetEndFunction<CBalrogLeft>("BalrogLeftAttack2", this, &CBalrogLeft::AnimationFinish);
	m_Anim->SetEndFunction<CBalrogLeft>("BalrogLeftDie", this, &CBalrogLeft::ArmDie);

	m_Sprite->AddChild(m_Body);

	m_Body->SetExtent(137.5f, 98.5f);

	SetCharacterInfo("BalrogLeft");

	return true;
}

void CBalrogLeft::Update(float DeltaTime)
{
	CObjectManager::Update(DeltaTime);
}

void CBalrogLeft::PostUpdate(float DeltaTime)
{
	CObjectManager::PostUpdate(DeltaTime);

	if (m_CharacterInfo.HP <= 0)
	{
		m_Anim->ChangeAnimation("BalrogLeftDie");

		if (m_Body)
		{
			m_Body->Destroy();
		}

		return;
	}

	switch (m_State)
	{
	case EMonster_State::Idle:
		AIIdle(DeltaTime);
		break;

	case EMonster_State::Attack:
		AIAttack(DeltaTime);
		break;

	case EMonster_State::Die:
		AIDeath(DeltaTime);
		break;
	}
}

CBalrogLeft* CBalrogLeft::Clone()
{
	return new CBalrogLeft(*this);
}

void CBalrogLeft::AIIdle(float DeltaTime)
{
	if (m_Anim->CheckCurrentAnimation("BalrogLeftDie"))
	{
		return;
	}

	m_ActiveTime += DeltaTime;

	if (m_ActiveTime > m_RandActive)
	{
		m_ActiveTime = 0.f;

		m_IsMove = rand() % 2;

		if (m_IsMove)
		{
			m_State = EMonster_State::Attack;
		}

		else
		{
			m_State = EMonster_State::Idle;
		}

		m_RandActive = (float)(rand() % 2);
	}
}

void CBalrogLeft::AIAttack(float DeltaTime)
{
	if (m_Anim->CheckCurrentAnimation("BalrogLeftAttack1") || m_Anim->CheckCurrentAnimation("BalrogLeftAttack2") || m_Anim->CheckCurrentAnimation("BalrogLeftDie"))
	{
		return;
	}

	int num = (rand() % 2) + 1;

	if (num == 1)
	{
		m_Anim->ChangeAnimation("BalrogLeftAttack1");
	}

	else
	{
		m_Anim->ChangeAnimation("BalrogLeftAttack2");
	}
}

void CBalrogLeft::AIDeath(float DeltaTime)
{
	
}

void CBalrogLeft::InitAnimation()
{
	std::vector<const TCHAR*> vecFileName;

	for (int i = 1; i <= 12; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/stand/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogLeftIdle", "BalrogLeftIdle", vecFileName);

	for (int i = 0; i < 12; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogLeftIdle", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 12; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 28; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/die/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogLeftDie", "BalrogLeftDie", vecFileName);

	for (int i = 0; i < 28; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogLeftDie", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 28; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 21; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/attack1/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogLeftAttack1", "BalrogLeftAttack1", vecFileName);

	for (int i = 0; i < 21; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogLeftAttack1", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 21; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 29; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/attack2/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogLeftAttack2", "BalrogLeftAttack2", vecFileName);

	for (int i = 0; i < 29; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogLeftAttack2", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 29; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();
}

void CBalrogLeft::ChangeAnim(float DeltaTime)
{
	if (!m_Anim->CheckCurrentAnimation("BalrogLeftDie"))
	{
		m_Anim->ChangeAnimation("BalrogLeftDie");
	}
}

void CBalrogLeft::AnimationFinish()
{
	int num = rand() % 2;

	if (num)
	{
		m_State = EMonster_State::Idle;

		m_Anim->ChangeAnimation("BalrogLeftIdle");
	}

	else
	{
		num = rand() % 2;

		if (num)
		{
			m_Anim->ChangeAnimation("BalrogLeftAttack1");
		}

		else
		{
			m_Anim->ChangeAnimation("BalrogLeftAttack2");
		}
	}
}

void CBalrogLeft::ArmDie()
{
	m_State = EMonster_State::Die;
}
