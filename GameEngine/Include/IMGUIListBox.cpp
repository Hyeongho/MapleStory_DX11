#include "IMGUIListBox.h"

CIMGUIListBox::CIMGUIListBox() : m_Select(false), m_SelectIndex(-1), m_PageItemCount(3), m_Flag(0)
{
}

CIMGUIListBox::~CIMGUIListBox()
{
}

bool CIMGUIListBox::Init()
{
    return true;
}

void CIMGUIListBox::Render()
{
    ImVec2 Size = ImVec2(m_Size.x, m_PageItemCount * ImGui::GetTextLineHeightWithSpacing());

    //ImGui::Text(m_Name.c_str());

    if (ImGui::BeginListBox(m_Name.c_str(), Size))
    {
        size_t  ItemCount = m_vecItemUTF8.size();

        for (size_t i = 0; i < ItemCount; ++i)
        {
            m_Select = m_SelectIndex == i;

            if (ImGui::Selectable(m_vecItemUTF8[i].c_str(), m_Select, m_Flag))
            {
                if (m_SelectIndex != i && m_SelectCallback)
                {
                    m_SelectCallback((int)i, m_vecItem[i].c_str());

                    m_SelectIndex = (int)i;
                }

                else if (m_SelectIndex == i && m_SelectCallback)
                {
                    //m_SelectCallback(-1, NULL);

                    m_Select = false;

                    m_SelectIndex = -1;
                }
            }

            if (m_Select)
            {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndListBox();
    }
}
