#pragma once

#include "IMGUIWidget.h"

enum class ImGuiText_Type
{
	String,
	Int,
	Float
};

class CIMGUITextInput :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;
	friend class CIMGUIModal;

protected:
	CIMGUITextInput();
	virtual ~CIMGUITextInput();

protected:
	char m_Text[1024];
	wchar_t m_wText[1024];
	char m_TextUTF8[1024];

	std::array<char, 1024> m_aText;

	char m_HintText[1024];
	wchar_t m_wHintText[1024];
	char m_HintTextUTF8[1024];
	bool m_MultiLine;
	ImGuiInputTextFlags	m_Flag;

	ImGuiText_Type m_TextType;

	int m_ValueInt;
	float m_ValueFloat;
	std::function<void()> m_InputCallback;

public:
	int GetValueInt() const
	{
		return m_ValueInt;
	}

	float GetValueFloat() const
	{
		return m_ValueFloat;
	}

	const wchar_t* GetText() const
	{
		return m_wText;
	}

	const char* GetTextUTF8() const
	{
		return m_TextUTF8;
	}

	const char* GetTextMultibyte()
	{
		return m_Text;
	}

	const char& GetKoreaData() const
	{
		return *m_Text;
	}

	std::array<char, 1024> GetArray() const
	{
		return m_aText;
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

	void SetHintText(const char* Text)
	{
		memset(m_wHintText, 0, sizeof(wchar_t) * 1024);
		memset(m_HintText, 0, sizeof(char) * 1024);
		memset(m_HintTextUTF8, 0, sizeof(char) * 1024);
		int	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text, -1, m_wHintText, Length);

		// UTF8로 변환한다.
		Length = WideCharToMultiByte(CP_UTF8, 0, m_wHintText, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, m_wHintText, -1, m_HintTextUTF8, Length, 0, 0);
	}

	void SetInt(int Value)
	{
		m_ValueInt = Value;
	}

	void SetFloat(float Value)
	{
		m_ValueFloat = Value;
	}

	void SetMultiLine(bool MultiLine)
	{
		m_MultiLine = MultiLine;
	}

	void AddFlag(ImGuiInputTextFlags_ Flag)
	{
		m_Flag |= Flag;
	}

	void ReadOnly(bool Enable)
	{
		if (Enable)
		{
			m_Flag |= ImGuiInputTextFlags_ReadOnly;
		}

		else if (m_Flag & ImGuiInputTextFlags_ReadOnly)
		{
			m_Flag ^= ImGuiInputTextFlags_ReadOnly;
		}
	}

	void EnablePassword(bool Enable)
	{
		if (Enable)
		{
			m_Flag |= ImGuiInputTextFlags_Password;
		}

		else if (m_Flag & ImGuiInputTextFlags_Password)
		{
			m_Flag ^= ImGuiInputTextFlags_Password;
		}
	}

	void SetTextType(ImGuiText_Type Type)
	{
		m_TextType = Type;
	}

	bool Empty() const
	{
		return strlen(m_Text) == 0;
	}

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename T>
	void SetCallback(T* Obj, void(T::* Func)())
	{
		m_InputCallback = std::bind(Func, Obj);
	}
};

