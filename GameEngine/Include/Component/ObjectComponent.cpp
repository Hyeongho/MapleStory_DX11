#include "ObjectComponent.h"

CObjectComponent::CObjectComponent()
{
	SetTypeID<CObjectComponent>();
	m_ComponentType = Component_Type::ObjectComponent;
}

CObjectComponent::CObjectComponent(const CObjectComponent& com) : CComponent(com)
{
}

CObjectComponent::~CObjectComponent()
{
}

void CObjectComponent::Start()
{
	CComponent::Start();
}
