#include "Graphics.h"
#include "Util.h"
#include "Window.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

void Graphics::Clear( float r, float g, float b ) const {
	
	const float rgba[4] = {
		r, g, b, 1.0f
	};

	pContext->ClearRenderTargetView(pRTV.Get(), rgba);
	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 0.0f, 0u);
}

void Graphics::Present() const {
	ThrowIfFailed( pSwap->Present( 1u, 0u ) );
}

Graphics::Graphics(HWND hWnd, int width, int height, bool isWindowed) {
	
	// create swap chain descriptor
	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.OutputWindow = hWnd;													//
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;								// the game isn't very graphics intensive, so discard should do for simplicity
	sd.Windowed = isWindowed;												// 
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;						// 
	sd.BufferCount = 2;														// use 1 backbuffer and 1 frontbuffer
	sd.Flags = 0u;															// no flags

	sd.BufferDesc.Width = width;											//
	sd.BufferDesc.Height = height;											// 
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;						// output as 32-bit BGRA non-normalized format
	sd.BufferDesc.RefreshRate.Numerator = 60u;								// 60 frames
	sd.BufferDesc.RefreshRate.Denominator = 1u;								// per 1 second
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// don't care about scanline ordering
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// don't care about scaling mode

	sd.SampleDesc.Count = 1u;												// no anti aliasing
	sd.SampleDesc.Quality = 0u;												//

	UINT deviceFlags = 0u;

#ifdef _DEBUG
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !_DEBUG

	ThrowIfFailed( D3D11CreateDeviceAndSwapChain(
		NULL,						// no adapter
		D3D_DRIVER_TYPE_HARDWARE,	// running on hardware
		NULL,						// no handle to software driver, as we are running on hardware
		deviceFlags,
		NULL,						// use default feature level
		0,							// feature level array length is 0, as we are using default
		D3D11_SDK_VERSION,			// use the SDK version we are developing in right now
		&sd,
		&pSwap,
		&pDevice,
		NULL,						// dont care about what featurelevel d3d11 ended up using
									// on modern hardware we can assume at least D3D_FEATURE_LEVEL_11_0.
		&pContext
	) );
	


	// create view of render target
	Microsoft::WRL::ComPtr<ID3D11Resource> pBB;
	ThrowIfFailed( pSwap->GetBuffer( 0u, __uuidof(ID3D11Resource), &pBB ) ); // get the swapchains first backbuffer
	ThrowIfFailed( pDevice->CreateRenderTargetView( pBB.Get(), nullptr, &pRTV ) ); // create rtv of it and store the interface in pRTV


	// create Z-Buffer

	// create and bind depth stencil state to output merger
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;							// we want z-buffering
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;	// on every pixel
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;			// and object with least depth is in front

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSS;
	pDevice->CreateDepthStencilState( &dsDesc, &pDSS );
	pContext->OMSetDepthStencilState( pDSS.Get(), 1u );

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDS; // pointer to texture holding depth and stencil info

	D3D11_TEXTURE2D_DESC dsd = {}; // depth stencil descriptor
	dsd.Width = width;							//
	dsd.Height = height;						//
	dsd.MipLevels = 1u;							// No ekstra layers for a depth stencil buffer
	dsd.ArraySize = 1u;							// 
	dsd.Format = DXGI_FORMAT_D32_FLOAT;			// use 32-bit floats in buffer
	dsd.SampleDesc.Count = 1u;					// no anti-aliasing
	dsd.SampleDesc.Quality = 0u;				//
	dsd.Usage = D3D11_USAGE_DEFAULT;			// read and write access from GPU
	dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;	// 

	pDevice->CreateTexture2D( &dsd, nullptr, &pDS ); // create depth stencil buffer

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {}; // depth stencil view descriptor
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;				// read it as 32-bit floats
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	// the texture is 2D
	dsvd.Texture2D.MipSlice = 0u;						// no mipmapping is used

	pDevice->CreateDepthStencilView( pDS.Get(), &dsvd, &pDSV ); // create view of depth stencil buffer

	pContext->OMSetRenderTargets( 1u, pRTV.GetAddressOf(), pDSV.Get() ); // bind render target and depth stencil buffers to output merger
	
}
