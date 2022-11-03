#include "ClientManager.h"
#include "Engine.h"
#include "resource.h"
#include "TalkManager.h"
#include "ClientSceneManager.h"
#include "Scene/SceneManager.h"
#include "Scene/StartScene.h"
#include "Scene/MainScene.h"
#include "Scene/TestScene.h"
#include "Input.h"
#include "Object/PlayerManager.h"
#include "Object/Player2D.h"
#include "Object/TileMap.h"
#include "Component/TileMapComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Render/RenderManager.h"

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager() : m_Data(nullptr)
{
}

CClientManager::~CClientManager()
{
	CEngine::DestroyInst();

	SAFE_DELETE(m_Data)

	CPlayerManager::DestroyInst();
	CTalkManager::DestroyInst();
	CClientSceneManager::DestroyInst();
}

bool CClientManager::Init(HINSTANCE hInst)
{
	if (!CEngine::GetInst()->Init(hInst, TEXT("MapleStory_DX11"), 1366, 768, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	if (!CPlayerManager::GetInst()->Init())
	{
		return false;
	}

	if (!CTalkManager::GetInst()->Init())
	{
		return false;
	}

	if (!CClientSceneManager::GetInst()->Init())
	{
		return false;
	}

	CSceneManager::GetInst()->SetCreateSceneModeFunction<CClientManager>(this, &CClientManager::CreateSceneMode);
	CSceneManager::GetInst()->SetCreateObjectFunction<CClientManager>(this, &CClientManager::CreateObject);
	CSceneManager::GetInst()->SetCreateComponentFunction<CClientManager>(this, &CClientManager::CreateComponent);

	CSceneManager::GetInst()->SetProjectType(Project_Type::Client);

	//CRenderManager::GetInst()->CreateLayer("Effect", INT_MAX);

	CInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
	CInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
	CInput::GetInst()->CreateKey("MoveUp", VK_UP);
	//CInput::GetInst()->CreateKey("Jump", 'A'); // AltŰ ���� �ذ� �Ǹ� Alt�� ���� 
	CInput::GetInst()->CreateKey("Jump", 'C'); // AltŰ ���� �ذ� �Ǹ� Alt�� ���� 
	//CInput::GetInst()->SetAltKey("Jump", true); // AltŰ ���� �ذ� �Ǹ� Alt�� ���� 

	CInput::GetInst()->CreateKey("PhantomBlow", 'A');

	CInput::GetInst()->CreateKey("BladeFury", 'S');

	CInput::GetInst()->CreateKey("BalrogAnim", 'D');
	CInput::GetInst()->CreateKey("BalrogLeftAnim", 'F');
	CInput::GetInst()->CreateKey("BalrogRightAnim", 'G');

	//CInput::GetInst()->CreateKey("Attack", VK_SPACE);
	//CInput::GetInst()->CreateKey("Attack1", VK_LBUTTON);

	CResourceManager::GetInst()->CreateSoundChannelGroup("BGM");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Skill");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Player");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Effect");
	CResourceManager::GetInst()->CreateSoundChannelGroup("UI");
	CResourceManager::GetInst()->SetVolume(70);

	LoadSound();
	LoadData();
	CreateLayer();
	LoadAnimation();

	return true;
}

void CClientManager::CreateDefaultSceneMode()
{
	CSceneManager::GetInst()->CreateSceneMode<CStartScene>();
}

int CClientManager::Run()
{
	return CEngine::GetInst()->Run();
}

void CClientManager::CreateSceneMode(CScene* Scene, size_t Type)
{
	Scene->SetProjectType(Project_Type::Client);
}

CGameObject* CClientManager::CreateObject(CScene* Scene, size_t Type)
{
	if (Type == typeid(CGameObject).hash_code())
	{
		CGameObject* Obj = Scene->LoadGameObject<CGameObject>();

		return Obj;
	}

	else if (Type == typeid(CPlayer2D).hash_code())
	{
		CPlayer2D* Obj = Scene->LoadGameObject<CPlayer2D>();

		return Obj;
	}

	else if (Type == typeid(CTileMap).hash_code())
	{
		CTileMap* Obj = Scene->LoadGameObject<CTileMap>();

		return Obj;
	}

	return nullptr;
}

CComponent* CClientManager::CreateComponent(CGameObject* Obj, size_t Type)
{
	if (Type == typeid(CSceneComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSceneComponent>();

		return Component;
	}

	else if (Type == typeid(CSpriteComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSpriteComponent>();

		return Component;
	}

	else if (Type == typeid(CStaticMeshComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CStaticMeshComponent>();

		return Component;
	}

	else if (Type == typeid(CTileMapComponent).hash_code())
	{
		CTileMapComponent* Component = Obj->LoadComponent<CTileMapComponent>();

		Component->EnableEditMode(false);

		return Component;
	}

	else if (Type == typeid(CColliderBox2D).hash_code())
	{
		CColliderBox2D* Component = Obj->LoadComponent<CColliderBox2D>();

		return Component;
	}

	return nullptr;
}

CharacterInfo CClientManager::FindData(const std::string& Name)
{
	auto iter = m_mapData.find(Name);

	if (iter == m_mapData.end())
	{
		return m_mapData.end()->second;
	}

	return iter->second;
}

void CClientManager::SetFade(bool Fade)
{
	m_Fade = Fade;

	CInput::GetInst()->SetKeyInput(not Fade);
}

void CClientManager::LoadData()
{
	m_Data = new CData;

	m_Data->LoadExcel("Datatable", TEXT("Datatable.xlsx"));

	libxl::Book* book = m_Data->GetBook();

	if (!book)
	{
		return;
	}

	int size = book->sheetCount();

	for (int i = 0; i < size; i++)
	{
		libxl::Sheet* sheet = book->getSheet(i);

		if (sheet)
		{
			const wchar_t* wSheetName = book->getSheetName(i);

			char* SheetName = CEngine::GetInst()->ConvertWCtoC(book->getSheetName(i));

			std::string str = SheetName;

			int FirstCol = sheet->firstCol() + 2;
			int LastCol = sheet->lastCol() + 2;

			for (int j = FirstCol; j < LastCol; j++)
			{
				if (sheet->readStr(j, 0))
				{
					char* ObjName = CEngine::GetInst()->ConvertWCtoC(sheet->readStr(j, 0));

					m_vecDataName.push_back(ObjName);

					CharacterInfo Data;

					Data.HP = (int)sheet->readNum(j, 1);
					Data.MaxHP = (int)sheet->readNum(j, 1);
					Data.MP = (int)sheet->readNum(j, 2);
					Data.MaxMP = (int)sheet->readNum(j, 2);

					Data.Attack = (int)sheet->readNum(j, 3);
					Data.Armor = (int)sheet->readNum(j, 4);

					Data.Level = (int)sheet->readNum(j, 5);

					Data.Exp = (int)sheet->readNum(j, 6);
					Data.MaxExp = 0;

					m_mapData.insert(std::make_pair(ObjName, Data));
				}
			}

			m_mapSheet.insert(std::make_pair(str, m_vecDataName));
		}
	}

	book->release();
}

void CClientManager::LoadSound()
{
	// BGM
	CResourceManager::GetInst()->LoadSound("BGM", true, "secretFlower", "secretFlower.mp3");
	CResourceManager::GetInst()->LoadSound("BGM", true, "EvilEyes", "EvilEyes.mp3");

	// Player
	CResourceManager::GetInst()->LoadSound("Player", false, "Jump", "Jump.mp3");

	// Effect
	

	// UI
}

void CClientManager::LoadAnimation()
{
	// Balrog Body
	std::vector<const TCHAR*> vecFileName;

	for (int i = 1; i <= 12; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/stand/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogBodyIdle", "BalrogBodyIdle", vecFileName);

	for (int i = 0; i < 12; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogBodyIdle", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 12; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 22; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/die/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[20]);
	vecFileName.push_back(vecFileName[21]);

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogBodyDie", "BalrogBodyDie", vecFileName);

	for (int i = 0; i < 59; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogBodyDie", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 22; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 24; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack1%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogBodyAttack1", "BalrogBodyAttack1", vecFileName);

	for (int i = 0; i < 24; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogBodyAttack1", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 24; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 16; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack2/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogBodyAttack2", "BalrogBodyAttack2", vecFileName);

	for (int i = 0; i < 16; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogBodyAttack2", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 16; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 19; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack3/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogBodyAttack3", "BalrogBodyAttack3", vecFileName);

	for (int i = 0; i < 19; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogBodyAttack3", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 19; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 17; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Body/attack4/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogBodyAttack4", "BalrogBodyAttack4", vecFileName);

	for (int i = 0; i < 17; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogBodyAttack4", Vector2(0.f, 0.f), Vector2(1500.f, 1500.f));
	}

	for (int i = 0; i < 17; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	// Balrog Left
	for (int i = 1; i <= 12; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/stand/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogLeftIdle", "BalrogLeftIdle", vecFileName);

	for (int i = 0; i < 12; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogLeftIdle", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 12; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 28; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/die/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogLeftDie", "BalrogLeftDie", vecFileName);

	for (int i = 0; i < 28; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogLeftDie", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 28; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 21; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/attack1/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogLeftAttack1", "BalrogLeftAttack1", vecFileName);

	for (int i = 0; i < 21; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogLeftAttack1", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 21; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 29; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Left/attack2/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogLeftAttack2", "BalrogLeftAttack2", vecFileName);

	for (int i = 0; i < 29; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogLeftAttack2", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 29; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	// Balrog Right
	for (int i = 1; i <= 12; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/stand/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogRightIdle", "BalrogRightIdle", vecFileName);

	for (int i = 0; i < 12; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogRightIdle", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 12; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 28; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/die/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogRightDie", "BalrogRightDie", vecFileName);

	for (int i = 0; i < 28; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogRightDie", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 28; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 21; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/attack1/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogRightAttack1", "BalrogRightAttack1", vecFileName);

	for (int i = 0; i < 21; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogRightAttack1", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 21; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 24; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/attack2/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogRightAttack2", "BalrogRightAttack2", vecFileName);

	for (int i = 0; i < 24; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogRightAttack2", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 24; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 1; i <= 19; i++)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Monster/Balrog/Right/attack3/%d.png"), i);

		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("BalrogRightAttack3", "BalrogRightAttack3", vecFileName);

	for (int i = 0; i < 19; i++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("BalrogRightAttack3", Vector2(0.f, 0.f), Vector2(1000.f, 1000.f));
	}

	for (int i = 0; i < 19; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();
}

void CClientManager::CreateLayer()
{
	CRenderManager::GetInst()->CreateLayer("BalrogHand", 4);
}
