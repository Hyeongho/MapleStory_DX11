#include "SpriteEditObject.h"
#include "Component/SpriteComponent.h"
#include "Animation/AnimationSequence2DInstance.h"

CSpriteEditObject::CSpriteEditObject() : m_Distance(600.f)
{
}

CSpriteEditObject::CSpriteEditObject(const CSpriteEditObject& obj) : CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Distance = obj.m_Distance;
}

CSpriteEditObject::~CSpriteEditObject()
{
}

bool CSpriteEditObject::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("SpriteEdit");

	SetRootComponent(m_Sprite);

	//m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	//m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->CreateAnimationInstance<CAnimationSequence2DInstance>();

	m_Sprite->GetAnimationInstance()->Stop();

	return true;
}

void CSpriteEditObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSpriteEditObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSpriteEditObject* CSpriteEditObject::Clone()
{
	return new CSpriteEditObject(*this);
}
