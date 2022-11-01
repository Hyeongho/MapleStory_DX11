#include "BalrogRight.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"
#include "Input.h"

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

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogRight");

	SetRootComponent(m_Sprite);

	m_Sprite->SetLayerName("BalrogHand");

	//std::vector<TCHAR*> m_vecFileName;
	//std::vector<std::wstring> vecBalrogBodyFileName;

	//m_Sprite->GetMaterial()->GetTextureHeight();

	m_Sprite->SetWorldScale(1000.f, 1000.f, 1.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldPos(0.f, 0.f, 0.f);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation("BalrogRightIdle", "BalrogRightIdle", true, 2.04f);
	m_Anim->AddAnimation("BalrogRightDie", "BalrogRightDie", false, 2.8f);
	m_Anim->AddAnimation("BalrogRightAttack1", "BalrogRightAttack1", false, 2.1f);
	m_Anim->AddAnimation("BalrogRightAttack2", "BalrogRightAttack2", false, 2.4f);
	m_Anim->AddAnimation("BalrogRightAttack3", "BalrogRightAttack3", false, 1.9f);

	m_Anim->SetCurrentAnimation("BalrogRightIdle");

	m_Anim->SetEndFunction<CBalrogRight>("BalrogLeftDie", this, &CBalrogRight::ArmDie);

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
	std::vector<const TCHAR*> vecFileName;

	for (int i = 1; i <= 12; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/stand/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogRightIdle", "BalrogRightIdle", vecFileName);

	for (int i = 0; i < 12; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogRightIdle", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
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

		wsprintf(FileName, TEXT("Monster/Balrog/Right/die/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogRightDie", "BalrogRightDie", vecFileName);

	for (int i = 0; i < 28; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogRightDie", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
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

		wsprintf(FileName, TEXT("Monster/Balrog/Right/attack1/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogRightAttack1", "BalrogRightAttack1", vecFileName);

	for (int i = 0; i < 21; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogRightAttack1", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 21; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 24; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/attack2/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogRightAttack2", "BalrogRightAttack2", vecFileName);

	for (int i = 0; i < 24; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogRightAttack2", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 24; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 19; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/attack3/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Scene->GetResource()->CreateAnimationSequence2D("BalrogRightAttack3", "BalrogRightAttack3", vecFileName);

	for (int i = 0; i < 19; i++)
	{
		m_Scene->GetResource()->AddAnimationSequence2DFrame("BalrogRightAttack3", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 19; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();
}

void CBalrogRight::ChangeAnim(float DeltaTime)
{
	if (!m_Anim->CheckCurrentAnimation("BalrogRightDie"))
	{
		m_Anim->ChangeAnimation("BalrogRightDie");
	}
}

void CBalrogRight::ArmDie()
{
}
