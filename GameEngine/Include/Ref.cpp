#include "Ref.h"

CRef::CRef() : m_RefCount(0), m_Enable(true), m_Active(true), m_TypeID(0)
{
}

CRef::~CRef()
{
}

void CRef::Save(FILE* File)
{
	int	Length = (int)m_Name.length();
	fwrite(&Length, sizeof(int), 1, File);
	fwrite(m_Name.c_str(), sizeof(char), Length, File);

	fwrite(&m_Enable, sizeof(bool), 1, File);
	fwrite(&m_Active, sizeof(bool), 1, File);
	fwrite(&m_TypeID, sizeof(size_t), 1, File);
}

void CRef::Load(FILE* File)
{
	int	Length = 0;
	fread(&Length, sizeof(int), 1, File);
	char Name[256] = {};

	fread(Name, sizeof(char), Length, File);

	m_Name = Name;

	fread(&m_Enable, sizeof(bool), 1, File);
	fread(&m_Active, sizeof(bool), 1, File);
	fread(&m_TypeID, sizeof(size_t), 1, File);
}
