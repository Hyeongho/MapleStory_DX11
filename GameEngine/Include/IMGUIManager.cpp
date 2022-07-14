#include "IMGUIManager.h"
#include "Device.h"
#include "PathManager.h"
#include "IMGUIWindow.h"
#include "IMGUIModal.h"
#include "IMGUITestWindow.h"

DEFINITION_SINGLE(CIMGUIManager)

CIMGUIManager::CIMGUIManager() : m_Context(nullptr), m_CurrentFont(nullptr)
{
}

CIMGUIManager::~CIMGUIManager()
{
	auto iter = m_mapWindow.begin();
	auto iterEnd = m_mapWindow.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

bool CIMGUIManager::Init(HWND hWnd)
{
	m_Context = ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	// BackEnd Setup
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(CDevice::GetInst()->GetDevice(), CDevice::GetInst()->GetContext());

	AddFont("Default", "KoPubDotumBold.ttf", 15.f, true);
	AddFont("DefaultBlack", "KoPubDotumBold.ttf", 15.f, true);
	AddFont("DefaultBold", "KoPubDotumBold.ttf", 15.f, true);

	m_CurrentFont = FindFont("Default");

	//CIMGUITestWindow* Window = AddWindow<CIMGUITestWindow>("TestWindow");

	return true;
}

void CIMGUIManager::Update(float DeltaTime)
{
	if (m_mapWindow.empty())
	{
		return;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	//ImGui::PushFont(m_CurrentFont);

	{
		auto iter = m_mapWindow.begin();
		auto iterEnd = m_mapWindow.end();

		for (; iter != iterEnd; iter++)
		{
			iter->second->Update(DeltaTime);
		}
	}

	{
		auto iter = m_mapModal.begin();
		auto iterEnd = m_mapModal.end();

		for (; iter != iterEnd; iter++)
		{
			iter->second->Update(DeltaTime);
		}
	}

	//ImGui::PopFont();

	// Window에서 그려낸 위젯들은 실제 화면에 그려지는것이 아니라
	// IMGUI 내부의 버퍼에 그려지게 된다.
	// 이 버퍼를 최종적으로 한번 그려내는 방식으로 처리가 된다.
	ImGui::Render();
}

void CIMGUIManager::Render()
{
	if (m_mapWindow.empty())
	{
		return;
	}

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

CIMGUIWindow* CIMGUIManager::FindIMGUIWindow(const std::string& Name)
{
	auto iter = m_mapWindow.find(Name);

	if (iter == m_mapWindow.end())
	{
		return nullptr;
	}

	return iter->second;
}

CIMGUIModal* CIMGUIManager::FindIMGUIModal(const std::string& Name)
{
	auto iter = m_mapModal.find(Name);

	if (iter == m_mapModal.end())
	{
		return nullptr;
	}

	return iter->second;
}

bool CIMGUIManager::AddFont(const std::string& Name, const char* FileName, float Size, bool Korea, int OverH, int OverV,
	float Spacing, const std::string& PathName)
{
	ImFont* Font = FindFont(Name);

	if (Font)
	{
		return false;
	}

	char FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
	{
		strcpy_s(FullPath, Info->PathMultibyte);
	}

	strcat_s(FullPath, FileName);

	return AddFontFullPath(Name, FullPath, Size, Korea, OverH, OverV, Spacing);
}

bool CIMGUIManager::AddFontFullPath(const std::string& Name, const char* FullPath, float Size, bool Korea, int OverH, int OverV, float Spacing)
{
	ImFont* Font = FindFont(Name);

	if (Font)
	{
		return false;
	}

	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig config;

	config.OversampleH = OverH;
	config.OversampleV = OverV;
	config.GlyphExtraSpacing.x = Spacing;
	config.PixelSnapH = 1;

	if (!Korea)
	{
		Font = io.Fonts->AddFontFromFileTTF(FullPath, Size, &config, io.Fonts->GetGlyphRangesDefault());
	}

	else
	{
		Font = io.Fonts->AddFontFromFileTTF(FullPath, Size, &config, io.Fonts->GetGlyphRangesKorean());
	}

	m_mapFont.insert(std::make_pair(Name, Font));

	return true;
}

void CIMGUIManager::SetCurrentFont(const std::string& Name)
{
	ImFont* Font = FindFont(Name);

	if (!Font)
	{
		return;
	}

	m_CurrentFont = Font;
}

ImFont* CIMGUIManager::FindFont(const std::string& Name)
{
	auto iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CIMGUIManager::SetCurrentFont()
{
	ImGui::PushFont(m_CurrentFont);
}

void CIMGUIManager::ResetCurrentFont()
{
	ImGui::PopFont();
}
