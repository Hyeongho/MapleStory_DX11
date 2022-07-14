
#include "SpriteMesh.h"

CSpriteMesh::CSpriteMesh()
{
}

CSpriteMesh::~CSpriteMesh()
{
}

bool CSpriteMesh::Init()
{
	MeshContainer	Container;

	Container.VB.Size = sizeof(VertexColor);
	Container.VB.Count = 4;
	Container.Primitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	VertexColor	Vtx[4] =
	{
		VertexColor(Vector3(-0.5f, 0.5f, 0.f), Vector4::Red),
		VertexColor(Vector3(0.5f, 0.5f, 0.f), Vector4::Green),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Blue),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f))
	};

	if (!CreateBuffer(Buffer_Type::Vertex, Vtx, sizeof(VertexColor),
		4, D3D11_USAGE_IMMUTABLE, &Container.VB.Buffer))
		return false;

	IndexBuffer	IdxBuffer;

	IdxBuffer.Size = 2;
	IdxBuffer.Count = 6;
	IdxBuffer.Fmt = DXGI_FORMAT_R16_UINT;

	unsigned short Idx[6] = { 0, 1, 3, 0, 3, 2 };

	if (!CreateBuffer(Buffer_Type::Index, Idx, sizeof(unsigned short),
		6, D3D11_USAGE_IMMUTABLE, &IdxBuffer.Buffer))
		return false;

	Container.vecIB.push_back(IdxBuffer);

	m_vecContainer.push_back(Container);

	return true;
}
