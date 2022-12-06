#include "Jr_BalrogAttack2Ball.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Jr_BalrogAttack2Hit.h"

CJr_BalrogAttack2Ball::CJr_BalrogAttack2Ball()
{
}

CJr_BalrogAttack2Ball::CJr_BalrogAttack2Ball(const CJr_BalrogAttack2Ball& obj) : CGameObject(obj)
{
	m_Sprite = obj.m_Sprite;
}

CJr_BalrogAttack2Ball::~CJr_BalrogAttack2Ball()
{
}

void CJr_BalrogAttack2Ball::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("Jr_BalrogAttack2Ball");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack2Ball.sqc"), ANIMATION_PATH, "Jr_BalrogAttack2Ball", true, 0.3f);

	Anim->SetEndFunction<CJr_BalrogAttack2Ball>("Jr_BalrogAttack2Ball", this, &CJr_BalrogAttack2Ball::AnimationFinish);
}

bool CJr_BalrogAttack2Ball::Init()
{
	CGameObject::Init();

	return true;
}

void CJr_BalrogAttack2Ball::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJr_BalrogAttack2Ball::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack2Ball* CJr_BalrogAttack2Ball::Clone()
{
	return new CJr_BalrogAttack2Ball(*this);
}

void CJr_BalrogAttack2Ball::AnimationFinish()
{
}

void CJr_BalrogAttack2Ball::CollisionCallbackBegin(const CollisionResult& result)
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

		Player->SetDamage(10.f);

		Destroy();
	}
}
