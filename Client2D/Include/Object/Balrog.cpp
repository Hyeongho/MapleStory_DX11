#include "Balrog.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"

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

	m_Sprite->AddChild(m_LeftMuzzle);
	m_Sprite->AddChild(m_RightMuzzle);

	m_LeftMuzzle->SetPivot(0.5f, 0.5f, 0.5f);
	m_RightMuzzle->SetPivot(0.5f, 0.5f, 0.5f);

	m_LeftMuzzle->SetWorldPos(-338.f, -170.f, 0.f);
	m_RightMuzzle->SetWorldPos(220.f, -170.f, 0.f);

	//std::vector<TCHAR*> m_vecFileName;
	//std::vector<std::wstring> vecBalrogBodyFileName;

	//m_Sprite->GetMaterial()->GetTextureHeight();

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(1500.f, 1500.f, 1.f);
	m_Sprite->SetWorldPos(500.f, 500.f, 0.f);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation("BalrogBodyIdle", "BalrogBodyIdle", true);

	m_Anim->SetCurrentAnimation("BalrogBodyIdle");

	m_BalrogLeft = m_Scene->CreateGameObject<CBalrogLeft>("BalrogLeft");
	m_BalrogRight = m_Scene->CreateGameObject<CBalrogRight>("BalrogRight");

	m_BalrogLeft->SetWorldPos(m_LeftMuzzle->GetWorldPos());
	m_BalrogRight->SetWorldPos(m_RightMuzzle->GetWorldPos());

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
	std::vector<TCHAR*> vecFileName;

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
}
