#pragma once

#include "IMGUIWindow.h"

class CDetailWindow :
	public CIMGUIWindow
{
public:
	CDetailWindow();
	virtual ~CDetailWindow();

private:
	class CIMGUITextInput* m_PosX;
	class CIMGUITextInput* m_PosY;
	class CIMGUITextInput* m_PosZ;

	class CIMGUITextInput* m_ScaleX;
	class CIMGUITextInput* m_ScaleY;
	class CIMGUITextInput* m_ScaleZ;

	class CIMGUITextInput* m_RotX;
	class CIMGUITextInput* m_RotY;
	class CIMGUITextInput* m_RotZ;

	class CIMGUITextInput* m_PivotX;
	class CIMGUITextInput* m_PivotY;
	class CIMGUITextInput* m_PivotZ;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:	
	void PositionXCallback();
	void PositionYCallback();
	void PositionZCallback();

	void ScaleXCallback();
	void ScaleYCallback();
	void ScaleZCallback();

	void LocationXCallback();
	void LocationYCallback();
	void LocationZCallback();

	void PivotXCallback();
	void PivotYCallback();
	void PivotZCallback();
};

