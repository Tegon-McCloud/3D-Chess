#include "BlendState.h"
#include "Window.h"
#include "Util.h"

BlendState::BlendState( bool blend ) {

	D3D11_BLEND_DESC bd = { 0 };
	D3D11_RENDER_TARGET_BLEND_DESC& rtbd = bd.RenderTarget[0];

	if ( blend ) {
		
		rtbd.BlendEnable = TRUE;
		rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	} else {

		rtbd.BlendEnable = FALSE;
		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	}

	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateBlendState( &bd, &pState ) );

}

void BlendState::Bind() {
	Window::Get().GetGraphics().GetContext()->OMSetBlendState( pState.Get(), NULL, 0xffffffffu );
}
