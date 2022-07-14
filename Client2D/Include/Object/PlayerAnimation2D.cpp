#include "PlayerAnimation2D.h"
#include "Player2D.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"

CPlayerAnimation2D::CPlayerAnimation2D()
{
	SetTypeID<CPlayerAnimation2D>();
}

CPlayerAnimation2D::CPlayerAnimation2D(const CPlayerAnimation2D& Anim) : CAnimationSequence2DInstance(Anim)
{
}

CPlayerAnimation2D::~CPlayerAnimation2D()
{
}

bool CPlayerAnimation2D::Init()
{
	if (!CAnimationSequence2DInstance::Init())
	{
		return false;
	}

	m_Player = (CPlayer2D*)m_Scene->GetPlayerObject();

	/*m_Player->m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	AddAnimation(TEXT("PlayerIdleM.sqc"), ANIMATION_PATH, "Idle", true);
	AddAnimation(TEXT("PlayerWalkM.sqc"), ANIMATION_PATH, "Walk", true);*/

	return true;
}

CPlayerAnimation2D* CPlayerAnimation2D::Clone()
{
	return new CPlayerAnimation2D(*this);
}

void CPlayerAnimation2D::Update(float DeltaTime)
{
	/*CAnimationSequence2DInstance::Update(DeltaTime);

	CPlayer2D* Player = (CPlayer2D*)m_Scene->GetPlayerObject();	
	
	if (Player)
	{
		if (!CheckCurrentAnimation("PlayerRightSwingD1") && Player->m_IsMove)
		{
			ChangeAnimation("PlayerRightSwingD1");
		}
	}*/
}


