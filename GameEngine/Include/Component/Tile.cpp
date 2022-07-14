#include "Tile.h"
#include "TileMapComponent.h"
#include "../Resource/Animation/AnimationSequence2D.h"

CTile::CTile() : m_Shape(Tile_Shape::Rect), m_TileType(Tile_Type::Normal), m_AnimInstance(nullptr), m_Owner(nullptr), m_IndexX(-1), m_IndexY(-1), m_Index(-1), m_Opacity(1.f)
{
}

CTile::CTile(const CTile& tile)
{
	*this = tile;

	m_AnimInstance = tile.m_AnimInstance->Clone();
}

CTile::~CTile()
{
	SAFE_DELETE(m_AnimInstance);
}

void CTile::AddAnimation(const std::string& SequenceName, const std::string& Name, bool Loop, float PlayTime, float PlayScale, bool Reverse)
{
	if (!m_AnimInstance)
	{
		m_AnimInstance = new CAnimationSequence2DInstance;
	}

	m_AnimInstance->AddAnimation(SequenceName, Name, Loop, PlayTime, PlayScale, Reverse);
}

void CTile::AddAnimation(const TCHAR* FileName, const std::string& PathName, const std::string& Name, bool Loop, float PlayTime, float PlayScale, bool Reverse)
{
	if (!m_AnimInstance)
	{
		m_AnimInstance = new CAnimationSequence2DInstance;
	}

	m_AnimInstance->AddAnimation(FileName, PathName, Name, Loop, PlayTime, PlayScale, Reverse);
}

void CTile::SetPlayTime(const std::string& Name, float PlayTime)
{
	if (!m_AnimInstance)
	{
		return;
	}

	m_AnimInstance->SetPlayTime(Name, PlayTime);
}

void CTile::SetPlayScale(const std::string& Name, float PlayScale)
{
	if (!m_AnimInstance)
	{
		return;
	}

	m_AnimInstance->SetPlayScale(Name, PlayScale);
}

void CTile::SetReverse(const std::string& Name, bool Reverse)
{
	if (!m_AnimInstance)
	{
		return;
	}

	m_AnimInstance->SetReverse(Name, Reverse);
}

void CTile::SetLoop(const std::string& Name, bool Loop)
{
	if (!m_AnimInstance)
	{
		return;
	}

	m_AnimInstance->SetLoop(Name, Loop);
}

void CTile::SetCurrentAnimation(const std::string& Name)
{
	if (!m_AnimInstance)
	{
		return;
	}

	m_AnimInstance->SetCurrentAnimation(Name);
}

void CTile::ChangeAnimation(const std::string& Name)
{
	if (!m_AnimInstance)
	{
		return;
	}

	m_AnimInstance->ChangeAnimation(Name);
}

bool CTile::CheckCurrentAnimation(const std::string& Name)
{
	if (!m_AnimInstance)
	{
		return false;
	}

	return m_AnimInstance->CheckCurrentAnimation(Name);
}

void CTile::Start()
{
	m_Center = m_Pos + m_Size / 2.f;
}

void CTile::Update(float DeltaTime, bool SortDiable)
{
	if (m_AnimInstance)
	{
		m_AnimInstance->Update(DeltaTime);

		int	Frame = m_AnimInstance->GetCurrentAnimation()->GetCurrentFrame();
		m_FrameStart = m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameData(Frame).Start;
		m_FrameEnd = m_FrameStart + m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameData(Frame).Size;
	}

	Vector3	OwnerPos = m_Owner->GetWorldPos();

	Vector3	Pos = OwnerPos + m_Pos;

	Vector3	WorldPos = Pos;

	if (CEngine::GetInst()->GetEngineSpace() == Engine_Space::Space2D)
	{
		if (SortDiable)
		{
			WorldPos.z = 999.9999f;
		}

		else
		{
			WorldPos.z = WorldPos.y / 30000.f * 1000.f;
		}
	}

	Matrix	matScale, matTranslate;

	matScale.Scaling(m_Size.x, m_Size.y, 1.f);
	matTranslate.Translation(WorldPos);

	m_matWorld = matScale * matTranslate;
}

void CTile::Save(FILE* File)
{
	fwrite(&m_Shape, sizeof(Tile_Shape), 1, File);
	fwrite(&m_TileType, sizeof(Tile_Type), 1, File);

	fwrite(&m_Pos, sizeof(Vector3), 1, File);
	fwrite(&m_Size, sizeof(Vector3), 1, File);
	fwrite(&m_Center, sizeof(Vector3), 1, File);

	fwrite(&m_IndexX, sizeof(int), 1, File);
	fwrite(&m_IndexY, sizeof(int), 1, File);
	fwrite(&m_Index, sizeof(int), 1, File);

	fwrite(&m_FrameStart, sizeof(Vector2), 1, File);
	fwrite(&m_FrameEnd, sizeof(Vector2), 1, File);

	fwrite(&m_Opacity, sizeof(float), 1, File);
}

void CTile::Load(FILE* File)
{
	fread(&m_Shape, sizeof(Tile_Shape), 1, File);
	fread(&m_TileType, sizeof(Tile_Type), 1, File);

	fread(&m_Pos, sizeof(Vector3), 1, File);
	fread(&m_Size, sizeof(Vector3), 1, File);
	fread(&m_Center, sizeof(Vector3), 1, File);

	fread(&m_IndexX, sizeof(int), 1, File);
	fread(&m_IndexY, sizeof(int), 1, File);
	fread(&m_Index, sizeof(int), 1, File);

	fread(&m_FrameStart, sizeof(Vector2), 1, File);
	fread(&m_FrameEnd, sizeof(Vector2), 1, File);

	fread(&m_Opacity, sizeof(float), 1, File);
}
