#pragma once

#include "Mesh.h"

class CStaticMesh :
    public CMesh
{
	friend class CMeshManager;

protected:
	CStaticMesh();
	virtual ~CStaticMesh();

public:
	virtual bool Init();
};

