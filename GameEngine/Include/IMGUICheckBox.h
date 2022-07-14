#pragma once

#include "IMGUIWidget.h"

class CIMGUICheckBox :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;
	friend class CIMGUIModal;

protected:
	CIMGUICheckBox();
	virtual ~CIMGUICheckBox();

protected:
	std::function<void(bool)> m_CheckCallback;
	bool m_Check;

public:
	virtual bool Init();
	virtual void Render();

public:
	void SetCheck(bool Check)
	{
		m_Check = Check;
	}

	bool getCheck() const
	{
		return m_Check;
	}

public:
	template <typename T>
	void SetCallback(T* Obj, void(T::* Func)(bool))
	{
		m_CheckCallback = std::bind(Func, Obj, std::placeholders::_1);
	}
};

