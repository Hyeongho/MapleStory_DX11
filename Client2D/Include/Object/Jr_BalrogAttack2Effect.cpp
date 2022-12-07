#include "Jr_BalrogAttack2Effect.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Jr_Balrog.h"
#include "Jr_BalrogAttack2Ball.h"
#include "Player2D.h"

CJr_BalrogAttack2Effect::CJr_BalrogAttack2Effect()
{
}

CJr_BalrogAttack2Effect::CJr_BalrogAttack2Effect(const CJr_BalrogAttack2Effect& obj) : CGameObject(obj)
{
}

CJr_BalrogAttack2Effect::~CJr_BalrogAttack2Effect()
{
}

void CJr_BalrogAttack2Effect::SetCollisionProfile(const std::string& Name)
{
}

void CJr_BalrogAttack2Effect::Start()
{
	CGameObject::Start();

	m_Anim->AddNotify<CJr_BalrogAttack2Effect>("Jr_BalrogAttack2Effect", "BallSpawn", 2, this, &CJr_BalrogAttack2Effect::BallSpawn);

	m_Body->Enable(false);
	Enable(false);
}

bool CJr_BalrogAttack2Effect::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("CJr_BalrogAttack2Effect");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Body->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Anim = m_Sprite->GetAnimationInstance();

	m_Anim->AddAnimation(TEXT("Monster/jr_Balrog/Jr_BalrogAttack2Effect.sqc"), ANIMATION_PATH, "Jr_BalrogAttack2Effect", true, 0.7f);
	m_Anim->SetEndFunction("Jr_BalrogAttack2Effect", this, &CJr_BalrogAttack2Effect::AnimationFinish);

	m_Body->AddCollisionCallback<CJr_BalrogAttack2Effect>(Collision_State::Begin, this, &CJr_BalrogAttack2Effect::OnCollisionBegin);
	m_Body->AddCollisionCallback<CJr_BalrogAttack2Effect>(Collision_State::End, this, &CJr_BalrogAttack2Effect::OnCollisionEnd);

	m_Body->SetExtent(250.f, 250.f);

	m_Sprite->SetLayerName("Effect");

	return true;
}

void CJr_BalrogAttack2Effect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CJr_BalrogAttack2Effect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CJr_BalrogAttack2Effect* CJr_BalrogAttack2Effect::Clone()
{
	return  new CJr_BalrogAttack2Effect(*this);
}

void CJr_BalrogAttack2Effect::SetEnable(CJr_Balrog* Balrog)
{
	if (!Balrog)
	{
		m_Body->Enable(false);
		Enable(false);

		return;
	}

	m_Balrog = Balrog;

	if (!Balrog->GetFlip())
	{
		m_Anim->SetAnimFlip(false);

		m_Sprite->SetRelativeScale(229.f, 122.f, 1.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(224.f, 295.f, 1.f);
	}

	else
	{
		m_Anim->SetAnimFlip(true);

		m_Sprite->SetRelativeScale(229.f, 122.f, 1.f);
		m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
		m_Sprite->SetRelativePos(247.f, 295.f, 1.f);
	}

	m_Body->Enable(true);
	Enable(true);

	m_Anim->AnimationReStart();
}

void CJr_BalrogAttack2Effect::OnCollisionBegin(const CollisionResult& result)
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

void CJr_BalrogAttack2Effect::OnCollisionEnd(const CollisionResult& result)
{
	m_Target = false;
}

void CJr_BalrogAttack2Effect::AnimationFinish()
{
	m_Body->Enable(false);
	Enable(false);
}

void CJr_BalrogAttack2Effect::BallSpawn()
{
	CJr_BalrogAttack2Ball* Jr_BalrogAttack2Ball = m_Scene->CreateGameObject<CJr_BalrogAttack2Ball>("Jr_BalrogAttack2Ball", "Jr_BalrogAttack2Ball", GetWorldPos(), Vector3(68.f, 34.f, 1.f));

	if (m_Target)
	{
		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(m_Scene->GetPlayerObject());

		Vector3 PlayerPos = Player->GetWorldPos();
		Vector3 BalrogPos = Jr_BalrogAttack2Ball->GetWorldPos();

		float Radian = atan((PlayerPos.y - BalrogPos.y) / (PlayerPos.x - BalrogPos.x));
		float Degree = RadianToDegree(Radian);

		if (Degree >= 90 || Degree <= -90)
		{
			Jr_BalrogAttack2Ball->SetWorldRotation(0.f, 0.f, 0.f);
		}

		else
		{
			Jr_BalrogAttack2Ball->SetWorldRotation(0.f, 0.f, Degree);
		}		
	}

	if (!m_Balrog->GetFlip())
	{
		Jr_BalrogAttack2Ball->SetFlip(false);
		Jr_BalrogAttack2Ball->SetDirection(-300.f);
	}

	else
	{
		Jr_BalrogAttack2Ball->SetFlip(true);
		Jr_BalrogAttack2Ball->SetDirection(300.f);
	}
}
