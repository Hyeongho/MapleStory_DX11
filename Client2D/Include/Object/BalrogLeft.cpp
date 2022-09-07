#include "BalrogLeft.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Scene/SceneResource.h"

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

	m_Sprite = CreateComponent<CSpriteComponent>("BalrogLeft");

	SetRootComponent(m_Sprite);

	m_Sprite->SetLayerName("BalrogHand");

	//std::vector<TCHAR*> m_vecFileName;
	//std::vector<std::wstring> vecBalrogBodyFileName;

	//m_Sprite->GetMaterial()->GetTextureHeight();

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetWorldScale(1000.f, 1000.f, 1.f);

	m_Sprite->SetWorldPos(0.f, 0.f, 0.f);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation("BalrogLeftIdle", "BalrogLeftIdle", true);

	m_Anim->SetCurrentAnimation("BalrogLeftIdle");

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
	std::vector<TCHAR*> vecFileName;

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
}
