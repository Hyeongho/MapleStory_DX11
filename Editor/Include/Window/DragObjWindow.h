#pragma once

#include "IMGUIWindow.h"

class CDragObjWindow :
    public CIMGUIWindow
{
public:
	CDragObjWindow();
	virtual ~CDragObjWindow();

private:
	class CIMGUIText* m_TextStartX;
	class CIMGUIText* m_TextStartY;
	class CIMGUIText* m_TextEndX;
	class CIMGUIText* m_TextEndY;
		
	class CIMGUIText* m_TextPosX;
	class CIMGUIText* m_TextPosY;
	class CIMGUIText* m_TextScaleX;
	class CIMGUIText* m_TextScaleY;
	class CIMGUIText* m_TextPivotX;
	class CIMGUIText* m_TextPivotY;

	class CIMGUITextInput* m_StartXInput;
	class CIMGUITextInput* m_StartYInput;
	class CIMGUITextInput* m_EndXInput;
	class CIMGUITextInput* m_EndYInput;

	class CIMGUITextInput* m_PosXInput;
	class CIMGUITextInput* m_PosYInput;

	class CIMGUITextInput* m_ScaleXInput;
	class CIMGUITextInput* m_ScaleYInput;

	class CIMGUITextInput* m_PivotXInput;
	class CIMGUITextInput* m_PivotYInput;

	class CIMGUICheckBox* m_CheckBox;

private:
	float m_StartX;
	float m_StartY;
	float m_EndX;
	float m_EndY;

	float m_PosX;
	float m_PosY;

	float m_ScaleX;
	float m_ScaleY;

	float m_PivotX;
	float m_PivotY;

	bool m_Check;

public:
	bool GetCheck() const
	{
		return m_Check;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void Print();

	void StartXCallBack();
	void StartYCallBack();
	void EndXCallBack();
	void EndYCallBack();

	void PosXCallBack();
	void PosYCallBack();

	void ScaleXCallBack();
	void ScaleYCallBack();

	void PivotXCallBack();
	void PivotYCallBack();

	void CheckCallBack(bool Check);
};

