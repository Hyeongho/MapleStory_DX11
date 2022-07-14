#pragma once

#include "Widget.h"

enum class TEXT_ALIGN_H
{
	Left,
	Center,
	Right
};

enum class TEXT_ALIGN_V
{
	Top,
	Middle,
	Bottom
};

class CText :
    public CWidget
{
	friend class CWidgetWindow;

protected:
	CText();
	CText(const CText& widget);
	virtual ~CText();

protected:
	TCHAR* m_Text;
	int m_TextCount;
	int m_TextCapacity;

protected:
	IDWriteTextFormat* m_Font;
	IDWriteTextLayout* m_Layout;
	ID2D1SolidColorBrush* m_ColorBrush;
	ID2D1RenderTarget* m_2DTarget;
	std::string m_FontKey;
	TCHAR* m_FontName;
	float m_FontSize;
	bool m_Alpha;
	float m_Opacity;
	Vector4 m_Color;

	// Shadow
	bool m_ShadowEnable;
	ID2D1SolidColorBrush* m_ShadowColorBrush;
	bool m_ShadowAlpha;
	float m_ShadowOpacity;
	Vector4 m_ShadowColor;
	Vector2 m_ShadowOffset;

	TEXT_ALIGN_H m_AlignH;
	TEXT_ALIGN_V m_AlignV;

public:
	const TCHAR* GetText() const
	{
		return m_Text;
	}

	int GetTextCount() const
	{
		return m_TextCount;
	}

	virtual void SetSize(const Vector2& Size)
	{
		CWidget::SetSize(Size);
		CreateTextLayout();
	}

	virtual void SetSize(float x, float y)
	{
		CWidget::SetSize(x, y);
		CreateTextLayout();
	}

public:
	void SetText(const TCHAR* Text)
	{
		int	Length = lstrlen(Text);

		if (Length + 1 > m_TextCapacity)
		{
			m_TextCapacity = Length + 1;

			SAFE_DELETE_ARRAY(m_Text);

			m_Text = new TCHAR[m_TextCapacity];

			memset(m_Text, 0, sizeof(TCHAR) * m_TextCapacity);
		}

		lstrcpy(m_Text, Text);
		m_TextCount = Length;

		CreateTextLayout();
	}

	void AddText(const TCHAR* Text)
	{
		int	Length = m_TextCount + lstrlen(Text);

		if (Length + 1 > m_TextCapacity)
		{
			m_TextCapacity = Length + 1;

			TCHAR* NewText = new TCHAR[m_TextCapacity];

			memset(NewText, 0, sizeof(TCHAR) * m_TextCapacity);

			lstrcpy(NewText, m_Text);

			SAFE_DELETE_ARRAY(m_Text);

			m_Text = NewText;
		}

		lstrcat(m_Text, Text);
		m_TextCount += lstrlen(Text);

		CreateTextLayout();
	}

	void pop_back()
	{
		if (m_TextCount > 0)
		{
			m_TextCount++;

			m_Text[m_TextCount] = 0;

			CreateTextLayout();
		}
	}

	void Clear()
	{
		if (m_TextCount > 0)
		{
			m_TextCount = 0;

			memset(m_Text, 0, sizeof(TCHAR) * m_TextCapacity);

			CreateTextLayout();
		}
	}

public:
	void SetFont(const std::string& Name);
	void SetFontSize(float Size);
	void SetAlignH(TEXT_ALIGN_H Align);
	void SetAlignV(TEXT_ALIGN_V Align);
	void SetColor(float r, float g, float b);
	void SetColor(unsigned char r, unsigned char g, unsigned char b);
	void SetColor(const Vector4& Color);
	void SetColor(unsigned int Color);
	void SetAlphaEnable(bool AlphaEnable);
	void SetOpacity(float Opacity);

	void SetShadowEnable(bool ShadowEnable);
	void SetShadowOffset(const Vector2& Offset);
	void SetShadowOffset(float x, float y);
	void SetShadowColor(float r, float g, float b);
	void SetShadowColor(unsigned char r, unsigned char g, unsigned char b);
	void SetShadowColor(const Vector4& Color);
	void SetShadowColor(unsigned int Color);
	void SetShadowAlphaEnable(bool AlphaEnable);
	void SetShadowOpacity(float Opacity);

	bool CreateTextLayout();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CText* Clone();
};

