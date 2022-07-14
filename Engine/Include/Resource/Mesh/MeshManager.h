#pragma once

#include "../../GameInfo.h"

class CMeshManager
{
	friend class CResourceManager;

private:
	CMeshManager();
	~CMeshManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CMesh>> m_mapMesh;

public:
	bool Init();
	class CMesh* FindMesh(const std::string& Name);
	void ReleaseMesh(const std::string& Name);
};

