#include "IMGUICheckBox.h"

CIMGUICheckBox::CIMGUICheckBox() : m_Check(false)
{
}

CIMGUICheckBox::~CIMGUICheckBox()
{
}

bool CIMGUICheckBox::Init()
{
	return true;
}

void CIMGUICheckBox::Render()
{
	if (ImGui::Checkbox(m_Name.c_str(), &m_Check))
	{
		m_CheckCallback(m_Check);
	}
}
