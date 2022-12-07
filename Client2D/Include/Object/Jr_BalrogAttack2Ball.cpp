#include "Jr_BalrogAttack2Ball.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"
#include "Player2D.h"
#include "Jr_BalrogAttack2Hit.h"

CJr_BalrogAttack2Ball::CJr_BalrogAttack2Ball() : m_Distance(600.f)
{
}

CJr_BalrogAttack2Ball::CJr_BalrogAttack2Ball(const CJr_BalrogAttack2Ball& obj) : CGameObject(obj)
{
	m_Sprite = obj.m_Sprite;
	m_Distance = obj.m_Distance;
}

CJr_BalrogAttack2Ball::~CJr_BalrogAttack2Ball()
{
}

void CJr_BalrogAttack2Ball::Start()
{
	CGameObject::Start();

	m_Sprite = CreateComponent<CSpriteComponent>("Jr_BalrogAttack2Ball");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	m_Body->SetCollisionProfile("MonsterAttack");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	Anim->AddAnimation(TEXT("Monster/Jr_Balrog/Jr_BalrogAttack2Ball.sqc"), ANIMATION_PATH, "Jr_BalrogAttack2Ball", true, 0.3f);

	Anim->SetEndFunction<CJr_BalrogAttack2Ball>("Jr_BalrogAttack2Ball", this, &CJr_BalrogAttack2Ball::AnimationFinish);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.5f);

	m_Sprite->SetRelativeScale(68.f, 34.f, 1.f);

	m_Body->SetExtent(34.f, 17.f);

	m_Sprite->SetLayerName("Effect");

	m_Distance = 600;
}

bool CJr_BalrogAttack2Ball::Init()
{
	CGameObject::Init();

	return true;
}

void CJr_BalrogAttack2Ball::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	float Dist = m_Direction * DeltaTime;

	AddRelativePos(GetWorldAxis(AXIS_X) * Dist);

	m_Distance -= fabs(m_Direction * DeltaTime);

	if (m_Distance <= 0.f)
	{
		Destroy();
	}
}

void CJr_BalrogAttack2Ball::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack2Ball* CJr_BalrogAttack2Ball::Clone()
{
	return new CJr_BalrogAttack2Ball(*this);
}

void CJr_BalrogAttack2Ball::SetFlip(bool Flip)
{
	CAnimationSequence2DInstance* Anim = m_Sprite->GetAnimationInstance();

	if (!Anim)
	{
		return;
	}

	Anim->SetAnimFlip(Flip);
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
