#include "IMGUIWindow.h"
#include "IMGUIWidget.h"
#include "IMGUIManager.h"

CIMGUIWindow::CIMGUIWindow() : m_Open(true), m_WindowFlag(ImGuiWindowFlags_NoCollapse), m_ModalPopup(false), m_ModalOpen(false)
{
}

CIMGUIWindow::~CIMGUIWindow()
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

void CIMGUIWindow::Open()
{
	m_Open = true;
}

void CIMGUIWindow::OpenModal()
{
	m_ModalOpen = true;
}

void CIMGUIWindow::Close()
{
	m_Open = false;
}

void CIMGUIWindow::ClosePopup()
{
	m_ModalOpen = false;

	/*size_t	Size = m_vecPopupWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_vecPopupWidget[i]);
	}

	m_vecPopupWidget.clear();*/
}

CIMGUIWidget* CIMGUIWindow::FindWidget(const std::string& Name)
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

bool CIMGUIWindow::Init()
{
	return true;
}

void CIMGUIWindow::Update(float DeltaTime)
{
	if (!m_Open)
	{
		return;
	}

	if (!ImGui::Begin(m_Name.c_str(), &m_Open, m_WindowFlag))
	{
		m_Open = false;
	}

	CIMGUIManager::GetInst()->SetCurrentFont();

	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_vecWidget[i]->Render();
	}

	if (m_ModalPopup)
	{
		if (m_ModalOpen)
		{
			ImGui::OpenPopup(m_PopupTitle.c_str());
		}

		if (ImGui::BeginPopupModal(m_PopupTitle.c_str(), &m_ModalOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (!m_vecPopupWidget.empty())
			{
				Size = m_vecPopupWidget.size();

				for (size_t i = 0; i < Size; i++)
				{
					m_vecPopupWidget[i]->Render();
				}
			}			

			if (!m_ModalOpen)
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	CIMGUIManager::GetInst()->ResetCurrentFont();

	ImGui::End();
}