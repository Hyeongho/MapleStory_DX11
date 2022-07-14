#include "DepthStencilState.h"
#include "../Device.h"

CDepthStencilState::CDepthStencilState() :
	m_StencilRef(0xffffffff),
	m_PrevStencilRef(0xffffffff)
{
	m_Type = RenderState_Type::DepthStencil;
}

CDepthStencilState::~CDepthStencilState()
{
}

bool CDepthStencilState::CreateState(bool DepthEnable, D3D11_DEPTH_WRITE_MASK DepthWriteMask, D3D11_COMPARISON_FUNC DepthFunc, bool StencilEnable,
	UINT8 StencilReadMask, UINT8 StencilWriteMask, D3D11_DEPTH_STENCILOP_DESC FrontFace, D3D11_DEPTH_STENCILOP_DESC BackFace)
{
	D3D11_DEPTH_STENCIL_DESC	Desc = {};

	Desc.DepthEnable = DepthEnable;
	Desc.DepthWriteMask = DepthWriteMask;
	Desc.DepthFunc = DepthFunc;
	Desc.StencilEnable = StencilEnable;
	Desc.StencilReadMask = StencilReadMask;
	Desc.StencilWriteMask = StencilWriteMask;
	Desc.FrontFace = FrontFace;
	Desc.BackFace = BackFace;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateDepthStencilState(&Desc, (ID3D11DepthStencilState**)&m_State)))
	{
		return false;
	}

	return true;
}

void CDepthStencilState::SetState()
{
	CDevice::GetInst()->GetContext()->OMGetDepthStencilState((ID3D11DepthStencilState**)&m_PrevState, &m_PrevStencilRef);

	CDevice::GetInst()->GetContext()->OMSetDepthStencilState((ID3D11DepthStencilState*)m_State, m_StencilRef);
}

void CDepthStencilState::ResetState()
{
	CDevice::GetInst()->GetContext()->OMSetDepthStencilState((ID3D11DepthStencilState*)m_PrevState, m_PrevStencilRef);

	SAFE_RELEASE(m_PrevState);
}
