#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()	: m_Device(nullptr), m_Context(nullptr), m_SwapChain(nullptr), m_TargetView(nullptr), m_DepthView(nullptr),
	m_2DTarget(nullptr), m_2DTargetWorld(nullptr), m_2DFactory(nullptr)
{
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_2DTarget);
	SAFE_RELEASE(m_2DTargetWorld);
	SAFE_RELEASE(m_2DFactory);

	SAFE_RELEASE(m_TargetView);
	SAFE_RELEASE(m_DepthView);

	SAFE_RELEASE(m_SwapChain);

	if (m_Context)
	{
		m_Context->ClearState();
	}

	SAFE_RELEASE(m_Context);
	SAFE_RELEASE(m_Device);
}

Vector2 CDevice::GetViewportAspectRatio()
{
	RECT ClientRC = {};

	GetClientRect(m_hWnd, &ClientRC);

	float Width = (float)(ClientRC.right - ClientRC.left);
	float Height = (float)(ClientRC.bottom - ClientRC.top);

	return Vector2(m_RS.Width / Width, m_RS.Height / Height);
}

bool CDevice::Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode)
{
	m_hWnd = hWnd;
	m_RS.Width = Width;
	m_RS.Height = Height;

	unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG

	Flag |= D3D11_CREATE_DEVICE_DEBUG;

#endif // _DEBUG

	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevel1 = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag, &FLevel, 1, D3D11_SDK_VERSION, &m_Device, &FLevel1, &m_Context)))
	{
		return false;
	}

	int	 SampleCount = 4;

	UINT Check = 0;
	m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Check);

	if (Check < 1)
	{
		SampleCount = 1;
	}

	DXGI_SWAP_CHAIN_DESC	SwapDesc = {};

	SwapDesc.BufferDesc.Width = Width;
	SwapDesc.BufferDesc.Height = Height;
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapDesc.BufferCount = 1;
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapDesc.OutputWindow = hWnd;
	SwapDesc.SampleDesc.Count = SampleCount;
	SwapDesc.SampleDesc.Quality = 0;
	SwapDesc.Windowed = WindowMode;
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGIDevice* DXGIDevice = nullptr;
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if (FAILED(Factory->CreateSwapChain(m_Device, &SwapDesc, &m_SwapChain)))
	{
		SAFE_RELEASE(DXGIDevice);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(Factory);
		return false;
	}

	SAFE_RELEASE(DXGIDevice);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(Factory);

	// SwapChain이 가지고 있는 백버퍼를 얻어온다.
	ID3D11Texture2D* BackBuffer = nullptr;

	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	// BackBuffer와 연결된 RenderTargetView를 생성한다.
	m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_TargetView);

	SAFE_RELEASE(BackBuffer);

	// 깊이버퍼를 만든다.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};

	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;

	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	ID3D11Texture2D* DepthBuffer = nullptr;

	m_Device->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer);

	m_Device->CreateDepthStencilView(DepthBuffer, nullptr, &m_DepthView);

	SAFE_RELEASE(DepthBuffer);

	D3D11_VIEWPORT	VP = {};

	VP.Width = (float)Width;
	VP.Height = (float)Height;
	VP.MaxDepth = 1.f;

	m_Context->RSSetViewports(1, &VP);

	// 2D Factory 생성
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_2DFactory)))
	{
		return false;
	}

	// 3D BackBuffer의 Surface를 얻어온다.
	IDXGISurface* BackSurface = nullptr;

	m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&BackSurface));

	// 2D용 렌더타겟을 만들어준다.
	D2D1_RENDER_TARGET_PROPERTIES	props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, 
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));

	if (FAILED(m_2DFactory->CreateDxgiSurfaceRenderTarget(BackSurface, props, &m_2DTarget)))
	{
		return false;
	}

	SAFE_RELEASE(BackSurface);

	return true;
}

void CDevice::ClearRenderTarget(float ClearColor[4])
{
	m_Context->ClearRenderTargetView(m_TargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	m_Context->ClearDepthStencilView(m_DepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::RenderStart()
{
	m_Context->OMSetRenderTargets(1, &m_TargetView, m_DepthView);
}

void CDevice::Flip()
{
	m_SwapChain->Present(0, 0);
}
