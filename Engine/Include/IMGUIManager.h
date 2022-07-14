#pragma once

#include "GameInfo.h"

class CIMGUIManager
{
private:
	ImGuiContext* m_Context;
	std::unordered_map<std::string, class CIMGUIWindow*> m_mapWindow;
	std::unordered_map<std::string, class CIMGUIModal*> m_mapModal;
	std::unordered_map<std::string, ImFont*> m_mapFont;
	ImFont* m_CurrentFont;

public:
	bool Init(HWND hWnd);
	void Update(float DeltaTime);
	void Render();
	class CIMGUIWindow* FindIMGUIWindow(const std::string& Name);
	class CIMGUIModal* FindIMGUIModal(const std::string& Name);

public:
	bool AddFont(const std::string& Name, const char* FileName, float Size, bool Korea = false, int OverH = 2, int OverV = 1, float Spacing = 1.f, const std::string& PathName = FONT_PATH);
	bool AddFontFullPath(const std::string& Name, const char* FullPath, float Size, bool Korea = false, int OverH = 2, int OverV = 1, float Spacing = 1.f);
	void SetCurrentFont(const std::string& Name);
	ImFont* FindFont(const std::string& Name);
	void SetCurrentFont();
	void ResetCurrentFont();

public:
	template <typename T>
	T* AddWindow(const std::string& Name)
	{
		T* Window = (T*)FindIMGUIWindow(Name);

		if (Window)
		{
			return Window;
		}

		Window = new T;

		Window->SetName(Name);
		if (!Window->Init())
		{
			SAFE_DELETE(Window);
			return nullptr;
		}

		m_mapWindow.insert(std::make_pair(Name, Window));

		return Window;
	}

	template <typename T>
	T* AddModal(const std::string& Name)
	{
		T* Modal = (T*)FindIMGUIModal(Name);

		if (Modal)
		{
			return Modal;
		}

		Modal = new T;

		Modal->SetName(Name);
		if (!Modal->Init())
		{
			SAFE_DELETE(Modal);
			return nullptr;
		}

		m_mapModal.insert(std::make_pair(Name, Modal));

		return Modal;
	}

	DECLARE_SINGLE(CIMGUIManager)
};

