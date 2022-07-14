#pragma once

#include "Widget.h"

class CNumber :
	public CWidget
{
	friend class CWidgetWindow;

protected:
	CNumber();
	CNumber(const CNumber& widget);
	virtual ~CNumber();

protected:
	WidgetImageInfo m_Info;
	int m_Number;
	std::vector<int> m_vecNumber;

	ID2D1RenderTarget* m_2DTarget;
	bool m_Alpha;
	float m_Opacity;

public:
	void SetNumber(int Number)
	{
		m_Number = Number;
	}

	void AddNumber(int Number)
	{
		m_Number += Number;
	}

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

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CNumber* Clone();
};

