#include "IMGUIComboBox.h"

CIMGUIComboBox::CIMGUIComboBox() : m_Select(false), m_SelectIndex(-1), m_PageItemCount(3), m_Flag(0)
{
}

CIMGUIComboBox::~CIMGUIComboBox()
{
}

bool CIMGUIComboBox::Init()
{
	m_PrevViewName = m_Name;

	return true;
}

void CIMGUIComboBox::Render()
{
	ImGui::PushItemWidth(m_Size.x);

	if (ImGui::BeginCombo(m_Name.c_str(), m_PrevViewName.c_str(), m_Flag))
	{
		size_t  ItemCount = m_vecItemUTF8.size();

		for (size_t i = 0; i < ItemCount; ++i)
		{
			m_Select = m_SelectIndex == i;

			if (ImGui::Selectable(m_vecItemUTF8[i].c_str(), m_Select))
			{
				if (m_SelectIndex != i && m_SelectCallback)
				{
					m_SelectCallback((int)i, m_vecItem[i].c_str());
				}

				m_PrevViewName = m_vecItemUTF8[i];

				m_SelectIndex = (int)i;
			}

			if (m_Select)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}
}

