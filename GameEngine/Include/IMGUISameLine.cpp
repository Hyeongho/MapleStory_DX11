#include "IMGUISameLine.h"

CIMGUISameLine::CIMGUISameLine() : m_OffsetX(0.f), m_Spacing(-1.f)
{
}

CIMGUISameLine::~CIMGUISameLine()
{
}

bool CIMGUISameLine::Init()
{
    return true;
}

void CIMGUISameLine::Render()
{
    ImGui::SameLine(m_OffsetX, m_Spacing);
}
