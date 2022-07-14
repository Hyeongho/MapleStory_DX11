#include "StaticMesh.h"

CStaticMesh::CStaticMesh()
{
	SetTypeID<CStaticMesh>();
}

CStaticMesh::~CStaticMesh()
{
}

bool CStaticMesh::Init()
{
	return true;
}
