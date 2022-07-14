#include "DamageFont.h"
#include "../Widget/DamageWidget.h"

CDamageFont::CDamageFont()
{
}

CDamageFont::CDamageFont(const CDamageFont& obj)
{
}

CDamageFont::~CDamageFont()
{
}

void CDamageFont::SetDamageNumber(int Damage)
{
	m_Number->SetNumber((float)Damage);
}

void CDamageFont::Start()
{
	m_LifeTime = 3.0f;
}

bool CDamageFont::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Widget = CreateComponent<CWidgetComponent>("DamageFont");

	m_Number = m_Widget->CreateWidgetWindow<CDamageWidget>("DamageFont");

	SetRootComponent(m_Widget);

	/*std::vector<std::wstring> vecNumberFileName;

	for (int i = 0; i < 10; ++i)
	{
		TCHAR FileName[256] = {};

		wsprintf(FileName, TEXT("DamageNumber/%d.bmp"), i);

		vecNumberFileName.push_back(FileName);
	}*/

	return true;
}

void CDamageFont::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_LifeTime > 0.f)
	{
		m_LifeTime -= DeltaTime;

		if (m_LifeTime <= 0.f)
		{
			Destroy();

			return;
		}
	}
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
