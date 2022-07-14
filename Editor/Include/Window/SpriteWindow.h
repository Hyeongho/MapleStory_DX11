#pragma once

#include "IMGUIWindow.h"

class CSpriteWindow :
	public CIMGUIWindow
{
public:
	CSpriteWindow();
	virtual ~CSpriteWindow();

private:
	class CIMGUIImage* m_Sprite;
	class CIMGUIImage* m_SpriteFrame;
	class CIMGUIListBox* m_AnimationList;
	class CIMGUIListBox* m_AnimationFrameList;
	class CIMGUITextInput* m_AnimName;
	class CIMGUITextInput* m_AnimFrameName;
	CSharedPtr<class CSpriteEditObject> m_SpriteObject;
	class CAnimationSequence2DInstance* m_AnimInstance;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	CSpriteEditObject* GetSpriteObject() const
	{
		return m_SpriteObject;
	}

public:
	void LoadTextureButton();
	void SpriteEditButton();
	void FlipButton();
	void AddAnimationButton();
	void AddAnimationFrameButton();
	void SelectAnimationFrame(int Index, const char* Item);
	void DeleteFrameButton();
	void PlayAnimation();
	void SelectAnimation(int Index, const char* Item);

	void SaveSequence();
	void LoadSequence();
	void SaveAnimation();
	void LoadAnimation();
};

