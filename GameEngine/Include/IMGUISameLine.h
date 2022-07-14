#pragma once
#include "IMGUIWidget.h"
class CIMGUISameLine :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;
	friend class CIMGUIModal;

protected:
	CIMGUISameLine();
	virtual ~CIMGUISameLine();

protected:
	// OffsetX 는 윈도우 창의 왼쪽으로부터 어느정도 위치만큼 떨어뜨린 후에 그려낼지를 정한다.
	float m_OffsetX;

	// 시작 위치로부터 떨어질 거리를 의미한다.
	float m_Spacing;

public:
	void SetOffsetX(float OffsetX)
	{
		m_OffsetX = OffsetX;
	}

	void SetSpacing(float Spacing)
	{
		m_Spacing = Spacing;
	}

public:
	virtual bool Init();
	virtual void Render();
};

