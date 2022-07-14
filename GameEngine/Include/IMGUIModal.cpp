#include "IMGUIModal.h"
#include "IMGUIWidget.h"
#include "IMGUIManager.h"

CIMGUIModal::CIMGUIModal() : m_Open(true), m_WindowFlag(ImGuiWindowFlags_AlwaysAutoResize), m_ModalPopup(false)
{
}

CIMGUIModal::~CIMGUIModal()
{
	size_t Size = m_vecPopupWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_vecPopupWidget[i]);
	}

	m_vecPopupWidget.clear();

	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_vecWidget[i]);
	}

	m_vecWidget.clear();
}

void CIMGUIModal::Open()
{
	m_Open = true;

	ImGui::OpenPopup(m_Name.c_str());
}

void CIMGUIModal::Close()
{
	m_Open = false;

	ImGui::CloseCurrentPopup();
}

void CIMGUIModal::ClosePopup()
{
	ImGui::CloseCurrentPopup();

	size_t Size = m_vecPopupWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_vecPopupWidget[i]);
	}

	m_vecPopupWidget.clear();

	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_vecWidget[i]);
	}

	m_vecWidget.clear();
}

CIMGUIWidget* CIMGUIModal::FindWidget(const std::string& Name)
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		if (m_vecWidget[i]->m_Name == Name)
		{
			return m_vecWidget[i];
		}
	}

	return nullptr;
}

bool CIMGUIModal::Init()
{
	return true;
}

void CIMGUIModal::Update(float DeltaTime)
{
	if (!m_Open)
	{
		return;
	}

	if (!ImGui::BeginPopupModal(m_Name.c_str(), &m_Open, m_WindowFlag))
	{
		m_Open = false;

		ImGui::CloseCurrentPopup();
	}

	CIMGUIManager::GetInst()->SetCurrentFont();

	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_vecWidget[i]->Render();
	}

	CIMGUIManager::GetInst()->ResetCurrentFont();

	ImGui::EndPopup();
}
