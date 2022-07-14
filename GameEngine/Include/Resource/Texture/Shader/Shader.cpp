
#include "Shader.h"

CShader::CShader()
{
}

CShader::CShader(const CShader& shader)
{
	*this = shader;
	m_RefCount = 0;
}

CShader::~CShader()
{
}
