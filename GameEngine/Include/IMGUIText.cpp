#include "IMGUIText.h"

CIMGUIText::CIMGUIText() : m_Text{}, m_wText{}, m_TextUTF8{}, m_TextType(Text_Type::UTF8)
{
}

CIMGUIText::~CIMGUIText()
{
}

bool CIMGUIText::Init()
{
    return true;
}

void CIMGUIText::Render()
{
	switch (m_TextType)
	{
	case Text_Type::Multibyte:
		ImGui::TextColored(m_Color.Value, m_Text);
		break;

	case Text_Type::UTF8:
		ImGui::TextColored(m_Color.Value, m_TextUTF8);
		break;
	}
}
