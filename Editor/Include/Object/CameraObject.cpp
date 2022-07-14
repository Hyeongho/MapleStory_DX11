#include "CameraObject.h"
#include "Component/StaticMeshComponent.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Scene/Scene.h"

CCameraObject::CCameraObject()
{
	SetTypeID<CCameraObject>();
}

CCameraObject::CCameraObject(const CCameraObject& obj) : CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CCameraObject::~CCameraObject()
{
}

void CCameraObject::Start()
{
	CGameObject::Start();
}

bool CCameraObject::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	m_Mesh->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Teemo", TEXT("Teemo.jpg"));

	SetRootComponent(m_Mesh);

	m_Mesh->SetRelativeScale(72.f, 71.f, 1.f);
	m_Mesh->SetRelativePos(100.f, 50.f, 0.f);
	m_Mesh->SetPivot(0.5f, 0.5f, 0.f);

	m_Camera = CreateComponent<CCameraComponent>("BaseCamera");

	m_Mesh->AddChild(m_Camera);

	return true;
}

void CCameraObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCameraObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CCameraObject* CCameraObject::Clone()
{
	return new CCameraObject(*this);
}
