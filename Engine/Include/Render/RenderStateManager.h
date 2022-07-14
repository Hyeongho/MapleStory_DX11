#pragma once

#include "../GameInfo.h"

class CRenderStateManager
{
    friend class CRenderManager;

private:
    CRenderStateManager();
    ~CRenderStateManager();

private:
    std::unordered_map<std::string, CSharedPtr<class CRenderState>>	m_mapRenderState;

public:
    bool Init();

public:
    void SetBlendFactor(const std::string& Name, float r, float g, float b, float a);
    void AddBlendInfo(const std::string& Name, bool BlendEnable = true, D3D11_BLEND SrcBlend = D3D11_BLEND_SRC_ALPHA,
        D3D11_BLEND DestBlend = D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP BlendOp = D3D11_BLEND_OP_ADD,
        D3D11_BLEND SrcBlendAlpha = D3D11_BLEND_ONE, D3D11_BLEND DestBlendAlpha = D3D11_BLEND_ZERO,
        D3D11_BLEND_OP BlendOpAlpha = D3D11_BLEND_OP_ADD, UINT8 RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL);
    bool CreateBlendState(const std::string& Name, bool AlphaToCoverageEnable, bool IndependentBlendEnable);

public:
    bool CreateDepthStencilState(const std::string& Name, bool DepthEnable = true, D3D11_DEPTH_WRITE_MASK DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
        D3D11_COMPARISON_FUNC DepthFunc = D3D11_COMPARISON_LESS, bool StencilEnable = false,
        UINT8 StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK, UINT8 StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK,
        D3D11_DEPTH_STENCILOP_DESC FrontFace = { D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS },
        D3D11_DEPTH_STENCILOP_DESC BackFace = { D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP , D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS });

public:
    class CRenderState* FindRenderState(const std::string& Name);
};

