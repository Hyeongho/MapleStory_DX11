#include "IMGUIButton.h"

CIMGUIButton::CIMGUIButton() : m_Click(false)
{
}

CIMGUIButton::~CIMGUIButton()
{
}

bool CIMGUIButton::Init()
{
    return true;
}

void CIMGUIButton::Render()
{
    m_Click = ImGui::Button(m_Name.c_str(), m_Size);

    if (m_Click && m_ClickCallback)
    {
        m_ClickCallback();
    }
}
