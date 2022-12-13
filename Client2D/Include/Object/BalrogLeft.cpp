#include "BalrogLeft.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"
#include "Input.h"
#include "LeftAttack1AreaWarning.h"
#include "LeftAttack2Hit.h"

CBalrogLeft::CBalrogLeft()
{
}

CBalrogLeft::CBalrogLeft(const CBalrogLeft& obj) : CMonsterManager(obj)
{
}

CBalrogLeft::~CBalrogLeft()
{
}

void CBalrogLeft::Start()
{
	CMonsterManager::Start();

	for (int i = 0; i < 4; i++)
	{
		std::string name = "LeftAttack1AreaWarning" + std::to_string(i);

		CLeftAttack1AreaWarning* LeftAttack1AreaWarning = m_Scene->CreateGameObject<CLeftAttack1AreaWarning>(name);
	}
}

bool CBalrogLeft::Init()
{
	CMonsterManager::Init();

	//InitAnimation();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogLeft");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_AttackBody = CreateComponent<CColliderBox2D>("AttackBody");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Monster");
	m_AttackBody->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetLayerName("BalrogHand");

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(1000.f, 1000.f, 1.f);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation("BalrogLeftIdle", "BalrogLeftIdle", true, 2.04f);
	m_Anim->AddAnimation("BalrogLeftDie", "BalrogLeftDie", false, 3.36f);
	m_Anim->AddAnimation("BalrogLeftAttack1", "BalrogLeftAttack1", false, 2.1f);
	m_Anim->AddAnimation("BalrogLeftAttack2", "BalrogLeftAttack2", false, 3.48f);

	m_Anim->SetCurrentAnimation("BalrogLeftIdle");

	m_Anim->AddNotify<CBalrogLeft>("BalrogLeftAttack1", "BalrogLeftAttack1", 0, this, &CBalrogLeft::PlayBalrogSound);
	m_Anim->AddNotify<CBalrogLeft>("BalrogLeftAttack2", "BalrogLeftAttack2", 0, this, &CBalrogLeft::PlayBalrogSound);
	m_Anim->AddNotify<CBalrogLeft>("BalrogLeftDie", "BalrogLeftDie", 0, this, &CBalrogLeft::PlayBalrogSound);

	m_Anim->AddNotify<CBalrogLeft>("BalrogLeftAttack2", "BalrogLeftAttack2", 20, this, &CBalrogLeft::Attack);

	m_Anim->SetEndFunction<CBalrogLeft>("BalrogLeftAttack1", this, &CBalrogLeft::AnimationFinish);
	m_Anim->SetEndFunction<CBalrogLeft>("BalrogLeftAttack2", this, &CBalrogLeft::AnimationFinish);
	m_Anim->SetEndFunction<CBalrogLeft>("BalrogLeftDie", this, &CBalrogLeft::ArmDie);

	m_AttackBody->AddCollisionCallback<CBalrogLeft>(Collision_State::Begin, this, &CBalrogLeft::OnCollisionBegin);
	m_AttackBody->AddCollisionCallback<CBalrogLeft>(Collision_State::End, this, &CBalrogLeft::OnCollisionEnd);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_AttackBody);

	m_Body->SetExtent(137.5f, 98.5f);
	m_AttackBody->SetExtent(226.5f, 132.f);

	SetCharacterInfo("BalrogLeft");

	m_Attack1AreaWarningPosX.push_back(83.f);
	m_Attack1AreaWarningPosX.push_back(230.f);
	m_Attack1AreaWarningPosX.push_back(377.f);
	m_Attack1AreaWarningPosX.push_back(524.f);
	m_Attack1AreaWarningPosX.push_back(671.f);
	m_Attack1AreaWarningPosX.push_back(818.f);
	m_Attack1AreaWarningPosX.push_back(965.f);
	m_Attack1AreaWarningPosX.push_back(1112.f);

	return true;
}

void CBalrogLeft::Update(float DeltaTime)
{
	CObjectManager::Update(DeltaTime);

	if (m_CharacterInfo.HP <= 0)
	{
		m_CharacterInfo.HP = 0;
	}
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

void CBalrogLeft::OnCollisionBegin(const CollisionResult& result)
{
	if (!result.Dest->GetCollisionProfile())
	{
		return;
	}

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (!Player)
		{
			return;
		}

		m_Target = true;
	}
}

void CBalrogLeft::OnCollisionEnd(const CollisionResult& result)
{
	m_Target = false;
}

void CBalrogLeft::PlayLeftAttack1AreaWarning()
{
	std::lock_guard<std::mutex> lock(m1);

	srand((unsigned int)time(0));

	std::vector<float> PosX = m_Attack1AreaWarningPosX;

	size_t size = m_Attack1AreaWarningPosX.size();

	for (int i = 0; i < 4; i++)
	{
		int Index = rand() % size;

		std::string name = "LeftAttack1AreaWarning" + std::to_string(i);

		CLeftAttack1AreaWarning* LeftAttack1AreaWarning = dynamic_cast<CLeftAttack1AreaWarning*>(m_Scene->FindObject(name));

		if (!LeftAttack1AreaWarning)
		{
			return;
		}

		LeftAttack1AreaWarning->SetEnable();

		LeftAttack1AreaWarning->SetWorldPos(PosX[Index], 105.f, 1.f);

		PosX.erase(PosX.begin() + Index);
		size--;
	}
}

void CBalrogLeft::AnimationFinish()
{
	if (m_Anim->CheckCurrentAnimation("BalrogLeftAttack1"))
	{
		t1 = std::thread(&CBalrogLeft::PlayLeftAttack1AreaWarning, this);

		t1.join();
	}

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

void CBalrogLeft::Attack()
{
	if (m_Target)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		if (!Player)
		{
			return;
		}

		if (m_Anim->CheckCurrentAnimation("BalrogLeftAttack1"))
		{

		}

		else if (m_Anim->CheckCurrentAnimation("BalrogLeftAttack2"))
		{
			CLeftAttack2Hit* LeftAttack2Hit = m_Scene->CreateGameObject<CLeftAttack2Hit>("LeftAttack2Hit", "LeftAttack2Hit", Player->GetWorldPos());

			CResourceManager::GetInst()->SoundPlay("BalrogLeftCharDam2");

			Player->SetDamage(10.f);

			Player->SetHurt(true);
		}
	}
}

void CBalrogLeft::PlayBalrogSound()
{
	if (m_Anim->CheckCurrentAnimation("BalrogLeftAttack1"))
	{
		CResourceManager::GetInst()->SoundPlay("BalrogLeftAttack1");
	}

	else if (m_Anim->CheckCurrentAnimation("BalrogLeftAttack2"))
	{
		CResourceManager::GetInst()->SoundPlay("BalrogLeftAttack2");
	}

	else if (m_Anim->CheckCurrentAnimation("BalrogLeftDie"))
	{
		CResourceManager::GetInst()->SoundPlay("BalrogLeftDie");
	}
}
