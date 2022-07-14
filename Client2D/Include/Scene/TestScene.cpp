#include "TestScene.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/TestMonster.h"
#include "Scene/SceneResource.h"
#include "../Object/TileMap.h"

CTestScene::CTestScene()
{
	SetTypeID<CTestScene>();
}

CTestScene::~CTestScene()
{
}

bool CTestScene::Init()
{
	//CreateMaterial();

	CreateAnimationSequence();

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.3f);
	}

	m_TestWidget = m_Scene->GetViewport()->CreateWidgetWindow<CTestWidget>("TestWidget");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.3f);
	}

	//CTileMap* TileMap = m_Scene->CreateGameObject<CTileMap>("TileMap");

	if (m_LoadingFunction)
	{
		m_LoadingFunction(false, 0.3f);
	}

	return true;
}

void CTestScene::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("TileMap");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Tile", TEXT("Floors.png"));

	Material->SetShader("TileMapShader");
	Material->SetRenderState("AlphaBlend");
}

void CTestScene::CreateAnimationSequence()
{
}
