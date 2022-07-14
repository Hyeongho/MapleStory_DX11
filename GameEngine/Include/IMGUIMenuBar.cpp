#include "IMGUIMenuBar.h"

CIMGUIMenuBar::CIMGUIMenuBar() : m_Select(false), m_SelectIndex(-1), m_PageItemCount(3)
{
}

CIMGUIMenuBar::~CIMGUIMenuBar()
{
}

bool CIMGUIMenuBar::Init()
{
    return true;
}

void CIMGUIMenuBar::Render()
{
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu(m_Name.c_str()))
		{
			size_t Size = m_vecItem.size();

			if (Size == 0)
			{
				m_SelectCallback(0, m_Name);
			}

			else
			{
				for (int i = 0; i < Size; i++)
				{
					m_Select = m_SelectIndex == i;

					if (ImGui::MenuItem(m_vecItem[i].Label.c_str(), m_vecItem[i].Shortcut.c_str()))
					{
						if (m_SelectIndex != i && m_SelectCallback)
						{
							m_SelectCallback((int)i, m_vecItem[i].Label);
						}

						m_SelectIndex = (int)i;
					}
				}
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	m_Select = false;

	m_SelectIndex = -1;
}
