#include "BalrogRight.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"

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

	m_Anim->AddAnimation("BalrogRightIdle", "BalrogRightIdle", true);

	m_Anim->SetCurrentAnimation("BalrogRightIdle");

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
	std::vector<TCHAR*> vecFileName;

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
}
