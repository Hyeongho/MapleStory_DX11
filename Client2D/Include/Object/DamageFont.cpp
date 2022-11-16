#include "DamageFont.h"
#include "Widget/Number.h"

CDamageFont::CDamageFont() : m_Opacity(1.0f)
{
}

CDamageFont::CDamageFont(const CDamageFont& obj) : CGameObject(obj)
{
}

CDamageFont::~CDamageFont()
{
}

void CDamageFont::Start()
{
}

bool CDamageFont::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	CWidgetComponent* Widget = CreateComponent<CWidgetComponent>("DamageFont");

	m_Number = Widget->CreateWidgetWindow<CDamageWidget>("DamageFont");

	return true;
}

void CDamageFont::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Opacity -= DeltaTime / 1.4f;

	if (m_Opacity < 0.f)
	{
		m_Number->Destroy();
	}

	m_Number->SetOpacity(m_Opacity);
}

void CDamageFont::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDamageFont::Render()
{
	CGameObject::Render();
}

CDamageFont* CDamageFont::Clone()
{
	return new CDamageFont(*this);
}
