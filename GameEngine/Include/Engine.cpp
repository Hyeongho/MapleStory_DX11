#include "Engine.h"
#include "Device.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Timer.h"
#include "Scene/SceneManager.h"
#include "Render/RenderManager.h"
#include "Input.h"
#include "IMGUIManager.h"
#include "ExcelManager.h"
#include "Collision/CollisionManager.h"
#include "Resource/Shader/GlobalConstantBuffer.h"
#include "Resource/Shader/StructuredBuffer.h"
#include <time.h>

DEFINITION_SINGLE(CEngine)

bool CEngine::m_Loop = true;

CEngine::CEngine() : m_ClearColor{}, m_Timer(nullptr), m_Start(false), m_Play(true), m_Space(Engine_Space::Space2D), m_MouseState(Mouse_State::Normal), 
	m_GlobalCBuffer(nullptr), m_GlobalAccTime(0.f)
{
	//_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(472012);

	/*m_ClearColor[0] = 1.f;
	m_ClearColor[1] = 1.f;
	m_ClearColor[2] = 1.f;*/
}

CEngine::~CEngine()
{
	CSceneManager::DestroyInst();

	m_RandomBuffer->ResetShader(90, (int)Buffer_Shader_Type::Compute);

	SAFE_DELETE(m_GlobalCBuffer);
	SAFE_DELETE(m_RandomBuffer);

	CInput::DestroyInst();

	CRenderManager::DestroyInst();

	CCollisionManager::DestroyInst();

	CPathManager::DestroyInst();

	CResourceManager::DestroyInst();

	CIMGUIManager::DestroyInst();

	CExcelManager::DestroyInst();

	CDevice::DestroyInst();

	SAFE_DELETE(m_Timer);
}

bool CEngine::Init(HINSTANCE hInst, const TCHAR* Name, unsigned int Width, unsigned int Height, int IconID, bool WindowMode)
{
	m_hInst = hInst;

	m_RS.Width = Width;
	m_RS.Height = Height;

	Register(Name, IconID);
	Create(Name);

	return Init(hInst, m_hWnd, Width, Height, WindowMode);
}

bool CEngine::Init(HINSTANCE hInst, HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode)
{
	m_hInst = hInst;
	m_hWnd = hWnd;

	m_RS.Width = Width;
	m_RS.Height = Height;

	m_Timer = new CTimer;

	// Device 초기화
	if (!CDevice::GetInst()->Init(m_hWnd, Width, Height, WindowMode))
	{
		return false;
	}

	if (!CPathManager::GetInst()->Init())
	{
		return false;
	}

	// 리소스 관리자 초기화
	if (!CResourceManager::GetInst()->Init())
	{
		return false;
	}

	// 충돌 관리자 초기화
	if (!CCollisionManager::GetInst()->Init())
	{
		return false;
	}

	// 입력 관리자 초기화
	if (!CInput::GetInst()->Init(m_hInst, m_hWnd))
	{
		return false;
	}

	// 엑셀 관리자 초기화
	if (!CExcelManager::GetInst()->Init())
	{
		return false;
	}

	// IMGUI 관리자 초기화
	if (!CIMGUIManager::GetInst()->Init(m_hWnd))
	{
		return false;
	}

	// 렌더링 관리자 초기화
	if (!CRenderManager::GetInst()->Init())
	{
		return false;
	}

	m_GlobalCBuffer = new CGlobalConstantBuffer;

	if (!m_GlobalCBuffer->Init())
	{
		return false;
	}

	m_GlobalCBuffer->SetResolution(m_RS);

	// 장면 관리자 초기화
	if (!CSceneManager::GetInst()->Init())
	{
		return false;
	}

	// 난수 전용 구조화버퍼 생성
	/*m_RandomBuffer = new CStructuredBuffer;

	m_RandomBuffer->Init("RandomBuffer", sizeof(float), 10000, 10, true);

	srand((unsigned int)time(0));
	rand();

	float RandNumber[10000] = {};

	for (int i = 0; i < 10000; i++)
	{
		RandNumber[i] = rand() % 10001 / 10000.f;
	}

	m_RandomBuffer->UpdateBuffer(RandNumber, 10000);


	m_RandomBuffer->SetShader(90, (int)Buffer_Shader_Type::Compute);*/

	// NoiseTexture
	/*CResourceManager::GetInst()->LoadTexture("GlobalNoiseTexture", TEXT("noise_01.png"));

	m_GlobalNoiseTexture = CResourceManager::GetInst()->FindTexture("GlobalNoiseTexture");

	m_GlobalNoiseTexture->SetShader(100, (int)Buffer_Shader_Type::All, 0);*/

	//m_GlobalCBuffer->SetNoiseResolution((float)m_GlobalNoiseTexture->GetWidth(), (float)m_GlobalNoiseTexture->GetHeight());

	return true;
}

int CEngine::Run()
{
	MSG msg = {};

	while (m_Loop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}

		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;
}

void CEngine::Logic()
{
	if (!m_Start)
	{
		m_Start = true;

		CSceneManager::GetInst()->Start();
	}

	m_Timer->Update();

	float DeltaTime = m_Timer->GetDeltaTime();

	if (!m_Play)
	{
		DeltaTime = 0.f;
	}

	CResourceManager::GetInst()->Update();

	m_GlobalAccTime += DeltaTime;

	m_GlobalCBuffer->SetDeltaTime(DeltaTime);
	m_GlobalCBuffer->SetAccTime(m_GlobalAccTime);

	m_GlobalCBuffer->UpdateCBuffer();

	CIMGUIManager::GetInst()->Update(DeltaTime);

	CInput::GetInst()->Update(DeltaTime);

	if (Update(DeltaTime))
	{
		return;
	}

	if (PostUpdate(DeltaTime))
	{
		return;
	}

	Render(DeltaTime);
}

bool CEngine::Update(float DeltaTime)
{
	if (CSceneManager::GetInst()->Update(DeltaTime))
	{
		return true;
	}

	return false;
}

bool CEngine::PostUpdate(float DeltaTime)
{
	if (CSceneManager::GetInst()->PostUpdate(DeltaTime))
	{
		return true;
	}

	return false;
}

bool CEngine::Render(float DeltaTime)
{
	CDevice::GetInst()->RenderStart();
	CDevice::GetInst()->ClearRenderTarget(m_ClearColor);
	CDevice::GetInst()->ClearDepthStencil(1.f, 0);

	/*CMesh* Mesh = CResourceManager::GetInst()->FindMesh("SpriteMesh");
	CShader* Shader = CResourceManager::GetInst()->FindShader("ColorMeshShader");

	Shader->SetShader();

	Mesh->Render();*/
	CRenderManager::GetInst()->Render();

	CIMGUIManager::GetInst()->Render();

	CDevice::GetInst()->Flip();

	return true;
}

ATOM CEngine::Register(const TCHAR* Name, int IconID)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;

	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hInstance = m_hInst;

	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IconID));

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;

	wcex.lpszClassName = Name;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IconID));

	return RegisterClassExW(&wcex);
}

BOOL CEngine::Create(const TCHAR* Name)
{
	m_hWnd = CreateWindowW(Name, Name, WS_OVERLAPPEDWINDOW, 0, 0, m_RS.Width, m_RS.Height, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	RECT rc = { 0, 0, (LONG)m_RS.Width, (LONG)m_RS.Height };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);

	UpdateWindow(m_hWnd);

	return TRUE;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return 1;
	}

	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_Loop = false;
		PostQuitMessage(0);
		break;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		switch (wParam)
		{
		case VK_LMENU:
		case VK_MENU:
		case VK_RMENU:
		case 'C':
		case 'c':
			return NULL;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
