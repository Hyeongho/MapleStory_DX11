#pragma once

#include "Widget.h"

class CImage :
    public CWidget
{
	friend class CWidgetWindow;

protected:
	CImage();
	CImage(const CImage& widget);
	virtual ~CImage();

protected:
	WidgetImageInfo	m_Info;
	std::function<void()> m_ClickCallback;

public:
	virtual void Enable(bool bEnable)
	{
		CWidget::Enable(bEnable);
	}

	void SetTexture(CTexture* Texture)
	{
		m_Info.Texture = Texture;

		SetUseTexture(true);
	}

	bool SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	bool SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath);
	void SetTextureTint(const Vector4& Tint);
	void SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void AddFrameData(const Vector2& Start, const Vector2& Size);
	void AddFrameData(int Count);
	void SetPlayTime(float PlayTime);
	void SetPlayScale(float PlayScale);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CImage* Clone();

public:
	template <typename T>
	void SetClickCallback(T* Obj, void (T::* Func)())
	{
		m_ClickCallback = std::bind(Func, Obj);
	}

	void SetClickCallback(void (*Func)())
	{
		m_ClickCallback = std::bind(Func);
	}
};

