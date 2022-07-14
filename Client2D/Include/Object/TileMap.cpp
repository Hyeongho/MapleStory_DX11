#include "TileMap.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Component/ColliderPixel.h"
#include "Engine.h"

CTileMap::CTileMap()
{
	SetTypeID<CTileMap>();
}

CTileMap::CTileMap(const CTileMap& obj) : CGameObject(obj)
{
	m_TileMap = (CTileMapComponent*)FindComponent("TileMap");
}

CTileMap::~CTileMap()
{
}

void CTileMap::Start()
{
	CGameObject::Start();
}

bool CTileMap::Init()
{
	m_TileMap = CreateComponent<CTileMapComponent>("TileMap");

	SetRootComponent(m_TileMap);

	m_TileMap->CreateTile(Tile_Shape::Rect, 100, 100, Vector3(160.f, 80.f, 0.f));

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	m_TileMap->SetTileMaterial(Material);

	m_TileMap->SetTileDefaultFrame(160.f, 80.f, 320.f, 160.f);

	return true;
}

void CTileMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTileMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTileMap* CTileMap::Clone()
{
	return new CTileMap(*this);
}

void CTileMap::CollisionCallback(const CollisionResult& result)
{
	result.Src->GetCollisionProfile();

	if (result.Dest->GetCollisionProfile()->Name == "Player")
	{
		MessageBox(0, TEXT("Click"), TEXT("Click"), MB_OK);
	}
}
