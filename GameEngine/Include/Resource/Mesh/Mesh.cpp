
#include "Mesh.h"
#include "../../Device.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
	size_t	Size = m_vecContainer.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecContainer[i]);
	}
}

bool CMesh::CreateMesh(void* VtxData, int Size, int Count, D3D11_USAGE Usage, 
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IdxData, int IdxSize, int IdxCount, 
	D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	MeshContainer* Container = new MeshContainer;

	Container->VB.Size = Size;
	Container->VB.Count = Count;
	Container->Primitive = Primitive;

	if (!CreateBuffer(Buffer_Type::Vertex, VtxData, Size, Count, Usage, &Container->VB.Buffer))
	{
		return false;
	}

	if (IdxData != nullptr)
	{
		Container->vecIB.resize(1);

		Container->vecIB[0].Size = IdxSize;
		Container->vecIB[0].Count = IdxCount;
		Container->vecIB[0].Fmt = Fmt;

		if (!CreateBuffer(Buffer_Type::Index, IdxData, IdxSize, IdxCount, IdxUsage, &Container->vecIB[0].Buffer))
		{
			return false;
		}
	}

	m_vecContainer.push_back(Container);

	return true;
}

bool CMesh::Init()
{
	return true;
}

bool CMesh::CreateBuffer(Buffer_Type Type, void* Data, int Size, int Count, D3D11_USAGE Usage, ID3D11Buffer** Buffer)
{
	D3D11_BUFFER_DESC Desc = {};
	
	Desc.ByteWidth = Size * Count;
	Desc.Usage = Usage;

	if (Type == Buffer_Type::Vertex)
	{
		Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	}

	else
	{
		Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	}

	if (Usage == D3D11_USAGE_DYNAMIC)
	{
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	else if (Usage == D3D11_USAGE_STAGING)
	{
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	}

	D3D11_SUBRESOURCE_DATA	BufferData = {};

	BufferData.pSysMem = Data;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, &BufferData, Buffer)))
	{
		return false;
	}


	if (Type == Buffer_Type::Vertex)
	{
		char* VertexData = (char*)Data;

		for (int i = 0; i < Count; ++i)
		{
			Vector3* Pos = (Vector3*)VertexData;
			VertexData += Size;

			if (m_Min.x > Pos->x)
			{
				m_Min.x = Pos->x;
			}

			if (m_Min.y > Pos->y)
			{
				m_Min.y = Pos->y;
			}

			if (m_Min.z > Pos->z)
			{
				m_Min.z = Pos->z;
			}

			if (m_Max.x < Pos->x)
			{
				m_Max.x = Pos->x;
			}

			if (m_Max.y < Pos->y)
			{
				m_Max.y = Pos->y;
			}

			if (m_Max.z < Pos->z)
			{
				m_Max.z = Pos->z;
			}
		}
	}

	return true;
}

void CMesh::Render()
{
	size_t Size = m_vecContainer.size();

	for (size_t i = 0; i < Size; ++i)
	{
		unsigned int Stride = (unsigned int)m_vecContainer[i]->VB.Size;
		unsigned int Offset = 0;

		CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecContainer[i]->Primitive);
		CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1, &m_vecContainer[i]->VB.Buffer, &Stride, &Offset);

		size_t IdxCount = m_vecContainer[i]->vecIB.size();

		if (IdxCount > 0)
		{
			for (size_t j = 0; j < IdxCount; ++j)
			{
				CDevice::GetInst()->GetContext()->IASetIndexBuffer(m_vecContainer[i]->vecIB[j].Buffer, m_vecContainer[i]->vecIB[j].Fmt, 0);
				CDevice::GetInst()->GetContext()->DrawIndexed(m_vecContainer[i]->vecIB[j].Count, 0, 0);
			}
		}

		else
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
			CDevice::GetInst()->GetContext()->Draw(m_vecContainer[i]->VB.Count, 0);
		}
	}
}

void CMesh::RenderInstancing(int Count)
{
	size_t	Size = m_vecContainer.size();

	for (size_t i = 0; i < Size; i++)
	{
		unsigned int Stride = (unsigned int)m_vecContainer[i]->VB.Size;
		unsigned int Offset = 0;

		CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecContainer[i]->Primitive);
		CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1, &m_vecContainer[i]->VB.Buffer, &Stride, &Offset);

		size_t	IdxCount = m_vecContainer[i]->vecIB.size();

		if (IdxCount > 0)
		{
			for (size_t j = 0; j < IdxCount; ++j)
			{
				CDevice::GetInst()->GetContext()->IASetIndexBuffer(m_vecContainer[i]->vecIB[j].Buffer, m_vecContainer[i]->vecIB[j].Fmt, 0);
				CDevice::GetInst()->GetContext()->DrawIndexedInstanced(m_vecContainer[i]->vecIB[j].Count, Count, 0, 0, 0);
			}
		}

		else
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
			CDevice::GetInst()->GetContext()->DrawInstanced(m_vecContainer[i]->VB.Count, Count, 0, 0);
		}
	}
}

void CMesh::RenderInstancing(ID3D11Buffer* InstancingBuffer, unsigned int InstanceSize, int Count)
{
	size_t Size = m_vecContainer.size();

	for (size_t i = 0; i < Size; ++i)
	{
		unsigned int Stride[2] = { (unsigned int)m_vecContainer[i]->VB.Size, InstanceSize };
		unsigned int Offset[2] = {};

		ID3D11Buffer* Buffer[2] = { m_vecContainer[i]->VB.Buffer , InstancingBuffer };

		CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecContainer[i]->Primitive);
		CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 2, Buffer, Stride, Offset);

		size_t IdxCount = m_vecContainer[i]->vecIB.size();

		if (IdxCount > 0)
		{
			for (size_t j = 0; j < IdxCount; ++j)
			{
				CDevice::GetInst()->GetContext()->IASetIndexBuffer(m_vecContainer[i]->vecIB[j].Buffer, m_vecContainer[i]->vecIB[j].Fmt, 0);
				CDevice::GetInst()->GetContext()->DrawIndexedInstanced(m_vecContainer[i]->vecIB[j].Count, Count, 0, 0, 0);
			}
		}

		else
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
			CDevice::GetInst()->GetContext()->DrawInstanced(m_vecContainer[i]->VB.Count, Count, 0, 0);
		}
	}
}