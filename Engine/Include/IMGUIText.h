#pragma once
#include "IMGUIWidget.h"
class CIMGUIText :
    public CIMGUIWidget
{
	friend class CIMGUIWindow;
	friend class CIMGUIModal;

protected:
	CIMGUIText();
	virtual ~CIMGUIText();

protected:
	char m_Text[1024];
	wchar_t m_wText[1024];
	char m_TextUTF8[1024];

	Text_Type m_TextType;

public:
	const char* GetTextMultibyte() const
	{
		return m_Text;
	}

	const wchar_t* GetText() const
	{
		return m_wText;
	}

public:
	void SetText(const char* Text)
	{
		memset(m_wText, 0, sizeof(wchar_t) * 1024);
		memset(m_Text, 0, sizeof(char) * 1024);
		memset(m_TextUTF8, 0, sizeof(char) * 1024);

		strcpy_s(m_Text, Text);

		int	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text, -1, m_wText, Length);

		// UTF8로 변환한다.
		Length = WideCharToMultiByte(CP_UTF8, 0, m_wText, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, m_wText, -1, m_TextUTF8, Length, 0, 0);
	}

	void AddText(const char* Text)
	{
		wchar_t	wText[1024] = {};
		int	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text, -1, wText, Length);

		strcat_s(m_Text, Text);

		lstrcat(m_wText, wText);

		// UTF8로 변환한다.
		Length = WideCharToMultiByte(CP_UTF8, 0, m_wText, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, m_wText, -1, m_TextUTF8, Length, 0, 0);
	}

	void SetTextType(Text_Type TextType)
	{
		m_TextType = TextType;
	}

public:
	virtual bool Init();
	virtual void Render();
};

