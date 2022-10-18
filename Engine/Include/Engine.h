#pragma once

#include "GameInfo.h"
#include "Timer.h"

class CEngine
{
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	Resolution m_RS;
	static bool m_Loop;
	float m_ClearColor[4];
	class CTimer* m_Timer;
	bool m_Start;
	bool m_Play;
	Engine_Space m_Space;
	Mouse_State m_MouseState;
	CSharedPtr<class CWidgetWindow> m_MouseWidget[(int)Mouse_State::Max];
	class CGlobalConstantBuffer* m_GlobalCBuffer;
	float m_GlobalAccTime;
	CSharedPtr<class CTexture> m_GlobalNoiseTexture;
	class CStructuredBuffer* m_RandomBuffer;

public:
	Engine_Space GetEngineSpace() const
	{
		return m_Space;
	}

	void SetEngineSpace(Engine_Space Space)
	{
		m_Space = Space;
	}

	bool IsPlay() const
	{
		return m_Play;
	}

	void SetPlay(bool Play)
	{
		m_Play = Play;
	}

	HWND GetWindowHandle() const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance() const
	{
		return m_hInst;
	}

	CTimer* GetTimer() const
	{
		return m_Timer;
	}

	void Exit()
	{
		DestroyWindow(m_hWnd);
	}

public:
	bool Init(HINSTANCE hInst, const TCHAR* Name, unsigned int Width, unsigned int Heught, int IconID, bool WindowMode = true);
	bool Init(HINSTANCE hInst, HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode = true);
	int Run();
	void Logic();

private:
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	bool Render(float DeltaTime);

private:
	ATOM Register(const TCHAR* Name, int IconID);
	BOOL Create(const TCHAR* Name);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	//wchar_t 에서 char 로의 형변환 함수
	char* ConvertWCtoC(const wchar_t* str)
	{
		char Text[1024];
		wchar_t wText[1024];

		memset(wText, 0, sizeof(wchar_t) * 1024);
		memset(Text, 0, sizeof(char) * 1024);

		//wcscpy_s(wText, 1024, str);

		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

		WideCharToMultiByte(CP_ACP, 0, str, -1, Text, strSize, 0, 0);

		static char path[1024];

		strncpy_s(path, 1024, Text, 1024);

		return path;
	}

	//char 에서 wchar_t 로의 형변환 함수
	wchar_t* ConverCtoWC(const char* str)
	{
		char* Text = new char[1024];
		wchar_t* wText = new wchar_t[1024];

		memset(wText, 0, sizeof(wchar_t) * 1024);
		memset(Text, 0, sizeof(char) * 1024);

		//strcpy_s(Text, str);

		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

		MultiByteToWideChar(CP_ACP, 0, str, (int)strlen(str) + 1, wText, strSize);

		static wchar_t wText1[1024];

		wcscpy_s(wText1, strSize,  wText);

		delete[] Text;
		delete[] wText;

		return wText1;
	}

public:
	template <typename T>
	T* CreateMouse(Mouse_State State, const std::string& Name)
	{
		T* Window = new T;

		Window->SetName(Name);

		if (!Window->Init())
		{
			SAFE_RELEASE(Window);
			return nullptr;
		}

		m_MouseWidget[(int)State] = Window;

		return Window;
	}

	DECLARE_SINGLE(CEngine)
};

