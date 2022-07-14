#pragma once

#include "GameObject/GameObject.h"
#include "Component/WidgetComponent.h"
#include "../Widget/DamageWidget.h"

class CDamageFont :
    public CGameObject
{
    friend class CScene;

protected:
	CDamageFont();
	CDamageFont(const CDamageFont& obj);
	virtual ~CDamageFont();

private:
	CSharedPtr<CWidgetComponent> m_Widget;
	CSharedPtr<CDamageWidget> m_Number;

	float m_Opacity;

public:
	void SetDamageNumber(int Damage)
	{
		m_Number->SetNumber((float)Damage);
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CDamageFont* Clone();
};

