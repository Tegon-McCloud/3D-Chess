#include "States.h"
#include "Util.h"
#include "Window.h"

#include "d3d11_2.h"

void BlendState::Init( ID3D11Device* pDevice ) {

	D3D11_BLEND_DESC bd = { 0 };
	D3D11_RENDER_TARGET_BLEND_DESC& rtbd = bd.RenderTarget[0];

	rtbd.BlendEnable = TRUE;
	rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;

	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ThrowIfFailed( pDevice->CreateBlendState( &bd, &pEnabledState ) );

	bd = { 0 };
	rtbd = bd.RenderTarget[0];

	rtbd.BlendEnable = FALSE;
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	ThrowIfFailed( pDevice->CreateBlendState( &bd, &pDisabledState ) );

}

void BlendState::Enabled( bool enabled ) const {
	Window::Get().GetGraphics().GetContext()->OMSetBlendState( ( enabled ? pEnabledState : pDisabledState ).Get(), NULL, 0xffffffffu );
}

void DepthState::Init( ID3D11Device* pDevice ) {
	D3D11_DEPTH_STENCIL_DESC dsd = { 0 };
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	dsd.StencilEnable = FALSE;

	ThrowIfFailed( pDevice->CreateDepthStencilState( &dsd, &pEnabledState ) );

	dsd.DepthEnable = FALSE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	dsd.StencilEnable = FALSE;

	ThrowIfFailed( pDevice->CreateDepthStencilState( &dsd, &pDisabledState ) );
}

void DepthState::Enabled( bool enabled ) const {
	Window::Get().GetGraphics().GetContext()->OMSetDepthStencilState( (enabled ? pEnabledState : pDisabledState).Get(), 1u );
}
