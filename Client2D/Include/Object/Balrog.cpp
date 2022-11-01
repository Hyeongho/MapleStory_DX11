#include "Balrog.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"
#include "Input.h"

CBalrog::CBalrog()
{
}

CBalrog::CBalrog(const CBalrog& obj)
{
}

CBalrog::~CBalrog()
{
	
}

void CBalrog::Start()
{
	CMonsterManager::Start();
}

bool CBalrog::Init()
{
	CMonsterManager::Init();

	InitAnimation();

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogBody");
	m_LeftMuzzle = CreateComponent<CSceneComponent>("LeftMuzzle");
	m_RightMuzzle = CreateComponent<CSceneComponent>("RightMuzzle");

	SetRootComponent(m_Sprite);

	m_BalrogLeft = m_Scene->CreateGameObject<CBalrogLeft>("BalrogLeft");
	m_BalrogRight = m_Scene->CreateGameObject<CBalrogRight>("BalrogRight");

	m_Sprite->AddChild(m_LeftMuzzle);
	m_Sprite->AddChild(m_RightMuzzle);

	m_LeftMuzzle->AddChild(m_BalrogLeft->GetRootComponent());
	m_RightMuzzle->AddChild(m_BalrogRight->GetRootComponent());

	m_LeftMuzzle->SetPivot(0.5f, 0.5f, 0.5f);
	m_RightMuzzle->SetPivot(0.5f, 0.5f, 0.5f);

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

	/*m_BalrogLeft->SetWorldPos(m_LeftMuzzle->GetWorldPos());
	m_BalrogRight->SetWorldPos(m_RightMuzzle->GetWorldPos());*/

	//m_BalrogLeft->SetWorldPos(0.f, 0.f, 0.f);
	//m_BalrogRight->SetWorldPos(0.f, 0.f, 0.f);

	//CInput::GetInst()->SetKeyCallback<CBalrog>("BalrogAnim", KeyState_Down, this, &CBalrog::ChangeAnim);

	return true;
}

void CBalrog::Update(float DeltaTime)
{
	CObjectManager::Update(DeltaTime);
}

void CBalrog::PostUpdate(float DeltaTime)
{
	CObjectManager::PostUpdate(DeltaTime);
}

CBalrog* CBalrog::Clone()
{
	return new CBalrog(*this);
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
