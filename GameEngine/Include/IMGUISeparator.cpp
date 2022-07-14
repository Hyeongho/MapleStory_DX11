#include "IMGUISeparator.h"

CIMGUISeparator::CIMGUISeparator()
{
}

CIMGUISeparator::~CIMGUISeparator()
{
}

bool CIMGUISeparator::Init()
{
	return true;
}

void CIMGUISeparator::Render()
{
	ImGui::Separator();
}
