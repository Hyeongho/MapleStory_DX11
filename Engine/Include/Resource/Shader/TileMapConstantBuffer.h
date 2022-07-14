#pragma once

#include "ConstantBufferBase.h"

class CTileMapConstantBuffer :
    public CConstantBufferBase
{
public:
	CTileMapConstantBuffer();
	CTileMapConstantBuffer(const CTileMapConstantBuffer& Buffer);
	virtual ~CTileMapConstantBuffer();

protected:
	TileMapCBuffer m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CTileMapConstantBuffer* Clone();

public:
	void SetImageSize(const Vector2& ImageSize)
	{
		m_BufferData.ImageSize = ImageSize;
	}

	void SetTileSize(const Vector2& TileSize)
	{
		m_BufferData.Size = TileSize;
	}

	void SetImageStart(const Vector2& Start)
	{
		m_BufferData.Start = Start;
	}

	void SetImageEnd(const Vector2& End)
	{
		m_BufferData.End = End;
	}

	void SetWVP(const Matrix& matWVP)
	{
		m_BufferData.matWVP = matWVP;
	}
};

