#pragma once

#include "GameInfo.h"

class CDevice
{
private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Context;
	IDXGISwapChain* m_SwapChain;

	// BackBuffer에 픽셀을 쓰기 위해 RenderTargetView를 만들고
	// BackBuffer를 이 TargetView에 연결해준다.
	ID3D11RenderTargetView* m_TargetView;

	// 깊이, 스텐실 값을 쓰기 위해 DepthStencilView를 만들고
	// 연결해준다.
	ID3D11DepthStencilView* m_DepthView;

	HWND m_hWnd;
	Resolution m_RS;

private:
	ID2D1RenderTarget* m_2DTarget;
	ID2D1RenderTarget* m_2DTargetWorld;
	ID2D1Factory* m_2DFactory;

public: 
	void SetResolution(unsigned int Width, unsigned int Height)
	{
		m_RS.Width = Width;
		m_RS.Height = Height;
	}

public:
	ID2D1RenderTarget* Get2DRenderTarget() const
	{
		return m_2DTarget;
	}

	ID2D1RenderTarget* Get2DWorldRenderTarget() const
	{
		return m_2DTargetWorld;
	}

	ID2D1Factory* Get2DFactory() const
	{
		return m_2DFactory;
	}


	ID3D11Device* GetDevice() const
	{
		return m_Device;
	}

	ID3D11DeviceContext* GetContext() const
	{
		return m_Context;
	}

	IDXGISwapChain* GetSwapChain() const
	{
		return m_SwapChain;
	}

	Resolution GetResolution() const
	{
		return m_RS;
	}

	Vector2 GetViewportAspectRatio();

public:
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode);
	void ClearRenderTarget(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void RenderStart();
	void Flip();

	DECLARE_SINGLE(CDevice)
};

