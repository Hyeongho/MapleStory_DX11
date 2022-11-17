#include "Balrog.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"
#include "Input.h"
#include "BodyAttack1AreaWarning.h"
#include "BodyAttack3AreaWarning.h"

CBalrog::CBalrog() : m_BTRun(true)
{
}

CBalrog::CBalrog(const CBalrog& obj) : CMonsterManager(obj)
{
}

CBalrog::~CBalrog()
{
	
}

void CBalrog::Start()
{
	CMonsterManager::Start();

	m_BalrogLeft->SetWorldPos(m_LeftMuzzle->GetWorldPos());
	m_BalrogRight->SetWorldPos(m_RightMuzzle->GetWorldPos());

	m_BT->Start();

	m_BossStatus = m_Scene->GetViewport()->FindWidgetWindow<CBossStatus>("BossStatus");

	float HP = (float)m_CharacterInfo.HP + m_BalrogLeft->GetCharacterInfo().HP + m_BalrogRight->GetCharacterInfo().HP;
	float MaxHP = (float)m_CharacterInfo.MaxHP + m_BalrogLeft->GetCharacterInfo().MaxHP + m_BalrogRight->GetCharacterInfo().MaxHP;

	m_BossStatus->SetHPPercent(HP / MaxHP);

	CBodyAttack1AreaWarning* BodyAttack1AreaWarning1 = m_Scene->CreateGameObject<CBodyAttack1AreaWarning>("BodyAttack1AreaWarning1");

	BodyAttack1AreaWarning1->SetWorldPos(83.f, 118.f, 1.f);

	CBodyAttack1AreaWarning* BodyAttack1AreaWarning2 = m_Scene->CreateGameObject<CBodyAttack1AreaWarning>("BodyAttack1AreaWarning2");

	BodyAttack1AreaWarning2->SetWorldPos(1366.f - 83.f - 547.f, 118.f, 1.f);

	for (int i = 0; i < 4; i++)
	{
		std::string name = "BodyAttack3AreaWarning1" + std::to_string(i);

		CBodyAttack3AreaWarning* BodyAttack3AreaWarning = m_Scene->CreateGameObject<CBodyAttack3AreaWarning>(name);
	}
}

bool CBalrog::Init()
{
	CMonsterManager::Init();

	//InitAnimation();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogBody");
	m_LeftMuzzle = CreateComponent<CSceneComponent>("LeftMuzzle");
	m_RightMuzzle = CreateComponent<CSceneComponent>("RightMuzzle"); 
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_BalrogLeft = m_Scene->CreateGameObject<CBalrogLeft>("BalrogLeft");
	m_BalrogRight = m_Scene->CreateGameObject<CBalrogRight>("BalrogRight");

	m_Body->SetCollisionProfile("Monster");

	m_Sprite->AddChild(m_LeftMuzzle);
	m_Sprite->AddChild(m_RightMuzzle);
	m_Sprite->AddChild(m_Body);

	//m_LeftMuzzle->AddChild(m_BalrogLeft->GetRootComponent());
	//m_RightMuzzle->AddChild(m_BalrogRight->GetRootComponent());

	m_LeftMuzzle->SetPivot(0.5f, 0.5f, 0.5f);
	m_RightMuzzle->SetPivot(0.5f, 0.5f, 0.5f);
	//m_AttackBody->SetPivot(0.5f, 0.5f, 0.5f);

	m_LeftMuzzle->SetWorldPos(-330.f, -170.f, 0.f);
	m_RightMuzzle->SetWorldPos(220.f, -170.f, 0.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(1500.f, 1500.f, 1.f);

	//m_Sprite->SetWorldPos(700.f, 400.f, 0.f);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation("BalrogBodyIdle", "BalrogBodyIdle", true);
	m_Anim->AddAnimation("BalrogBodyDie", "BalrogBodyDie", false, 5.9f);
	m_Anim->AddAnimation("BalrogBodyAttack1", "BalrogBodyAttack1", false, 2.4f);
	m_Anim->AddAnimation("BalrogBodyAttack2", "BalrogBodyAttack2", false, 1.6f);
	m_Anim->AddAnimation("BalrogBodyAttack3", "BalrogBodyAttack3", false, 1.9f);
	m_Anim->AddAnimation("BalrogBodyAttack4", "BalrogBodyAttack4", false, 1.7f);

	m_Anim->SetCurrentAnimation("BalrogBodyIdle");

	m_Anim->SetEndFunction<CBalrog>("BalrogBodyAttack1", this, &CBalrog::AnimationFinish);
	m_Anim->SetEndFunction<CBalrog>("BalrogBodyAttack2", this, &CBalrog::AnimationFinish);
	m_Anim->SetEndFunction<CBalrog>("BalrogBodyAttack3", this, &CBalrog::AnimationFinish);
	m_Anim->SetEndFunction<CBalrog>("BalrogBodyAttack4", this, &CBalrog::AnimationFinish);

	m_BalrogLeft->SetWorldPos(m_LeftMuzzle->GetWorldPos());
	m_BalrogRight->SetWorldPos(m_RightMuzzle->GetWorldPos());

	m_Anim->AddNotify<CBalrog>("BalrogBodyAttack1", "BalrogBodyAttack1", 2, this, &CBalrog::SetAttackRange);

	//m_BalrogLeft->SetWorldPos(0.f, 0.f, 0.f);
	//m_BalrogRight->SetWorldPos(0.f, 0.f, 0.f);

	//CInput::GetInst()->SetKeyCallback<CBalrog>("BalrogAnim", KeyState_Down, this, &CBalrog::ChangeAnim);

	m_Attack3AreaWarningPosX.push_back(83);
	m_Attack3AreaWarningPosX.push_back(243);
	m_Attack3AreaWarningPosX.push_back(403);
	m_Attack3AreaWarningPosX.push_back(563);
	m_Attack3AreaWarningPosX.push_back(723);
	m_Attack3AreaWarningPosX.push_back(883);
	m_Attack3AreaWarningPosX.push_back(1043);

	m_Body->SetExtent(0.f, 0.f);

	m_BT = new CBalrogBT;

	SetCharacterInfo("Balrog");

	return true;
}

void CBalrog::Update(float DeltaTime)
{
	CObjectManager::Update(DeltaTime);

	float HP = (float)m_CharacterInfo.HP + m_BalrogLeft->GetCharacterInfo().HP + m_BalrogRight->GetCharacterInfo().HP;
	float MaxHP = (float)m_CharacterInfo.MaxHP + m_BalrogLeft->GetCharacterInfo().MaxHP + m_BalrogRight->GetCharacterInfo().MaxHP;

	m_BossStatus->SetHPPercent(HP / MaxHP);

	m_BT->Run(m_BTRun);
}

void CBalrog::PostUpdate(float DeltaTime)
{
	CObjectManager::PostUpdate(DeltaTime);

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

CBalrog* CBalrog::Clone()
{
	return new CBalrog(*this);
}

void CBalrog::AIIdle(float DeltaTime)
{
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

void CBalrog::AIAttack(float DeltaTime)
{
	if (m_Attack)
	{
		return;
	}

	int num = (rand() % 4) + 1;

	if (num == 1)
	{
		m_Anim->ChangeAnimation("BalrogBodyAttack1");
	}

	else if (num == 2)
	{
		m_Anim->ChangeAnimation("BalrogBodyAttack2");
	}

	else if (num == 3)
	{
		m_Anim->ChangeAnimation("BalrogBodyAttack3");
	}

	else if (num == 4)
	{
		m_Anim->ChangeAnimation("BalrogBodyAttack4");
	}

	m_Attack = true;
}

void CBalrog::AIDeath(float DeltaTime)
{
}

void CBalrog::InitAnimation()
{
	std::vector<const TCHAR*> vecFileName;

	for (int i = 1; i <= 12; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/stand/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogBodyIdle", "BalrogBodyIdle", vecFileName);

	for (int i = 0; i < 12; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogBodyIdle", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 12; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 22; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/die/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogBodyDie", "BalrogBodyDie", vecFileName);

	for (int i = 0; i < 59; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogBodyDie", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 22; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 24; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack1%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogBodyAttack1", "BalrogBodyAttack1", vecFileName);

	for (int i = 0; i < 24; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogBodyAttack1", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 24; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 16; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack2/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogBodyAttack2", "BalrogBodyAttack2", vecFileName);

	for (int i = 0; i < 16; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogBodyAttack2", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 16; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 19; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack3/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogBodyAttack3", "BalrogBodyAttack3", vecFileName);

	for (int i = 0; i < 19; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogBodyAttack3", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 19; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 17; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack4/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogBodyAttack4", "BalrogBodyAttack4", vecFileName);

	for (int i = 0; i < 17; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogBodyAttack4", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 17; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();
}

void CBalrog::AnimationFinish()
{
	if (m_Anim->CheckCurrentAnimation("BalrogBodyAttack1"))
	{
		t1 = std::thread(&CBalrog::PlayBodyAttack1AreaWarning, this);

		t1.join();
	}

	else if (m_Anim->CheckCurrentAnimation("BalrogBodyAttack2"))
	{

	}

	else if (m_Anim->CheckCurrentAnimation("BalrogBodyAttack3"))
	{
		t2 = std::thread(&CBalrog::PlayBodyAttack3AreaWarning, this);

		t2.join();
	}

	else if (m_Anim->CheckCurrentAnimation("BalrogBodyAttack4"))
	{

	}

	int num = rand() % 2;

	if (num)
	{
		m_State = EMonster_State::Idle;

		m_Anim->ChangeAnimation("BalrogBodyIdle");
	}

	else
	{
		m_State = EMonster_State::Attack;
	}

	m_Attack = false;
}

void CBalrog::SetAttackRange()
{
}

void CBalrog::Attack()
{
}

void CBalrog::ChangeAnim(float DeltaTime)
{
	if (!m_Anim->CheckCurrentAnimation("BalrogBodyDie"))
	{
		m_Anim->ChangeAnimation("BalrogBodyDie");

		m_Sprite->AddWorldPos(8.f, 0.f, 0.f);

		m_BalrogLeft->Destroy();
		m_BalrogRight->Destroy();
	}
}

void CBalrog::PlayBodyAttack1AreaWarning()
{
	std::lock_guard<std::mutex> lock(m1);

	CBodyAttack1AreaWarning* BodyAttack1AreaWarning1 = dynamic_cast<CBodyAttack1AreaWarning*>(m_Scene->FindObject("BodyAttack1AreaWarning1"));

	BodyAttack1AreaWarning1->SetEnable();

	BodyAttack1AreaWarning1->SetWorldPos(83.f, 118.f, 1.f);

	CBodyAttack1AreaWarning* BodyAttack1AreaWarning2 = dynamic_cast<CBodyAttack1AreaWarning*>(m_Scene->FindObject("BodyAttack1AreaWarning2"));

	BodyAttack1AreaWarning2->SetEnable();

	BodyAttack1AreaWarning2->SetWorldPos(1366.f - 83.f - 547.f, 118.f, 1.f);
}

void CBalrog::PlayBodyAttack3AreaWarning()
{
	std::lock_guard<std::mutex> lock(m2);

	srand((unsigned int)time(0));

	std::vector<float> PosX = m_Attack3AreaWarningPosX;

	size_t size = m_Attack3AreaWarningPosX.size();

	for (int i = 0; i < 4; i++)
	{
		int Index = rand() % size;

		std::string name = "BodyAttack3AreaWarning1" + std::to_string(i);

		CBodyAttack3AreaWarning* BodyAttack3AreaWarning = dynamic_cast<CBodyAttack3AreaWarning*>(m_Scene->FindObject(name));

		BodyAttack3AreaWarning->SetEnable();

		BodyAttack3AreaWarning->SetWorldPos(PosX[Index], 98.f, 1.f);

		PosX.erase(PosX.begin() + Index);
		size--;
	}
}
