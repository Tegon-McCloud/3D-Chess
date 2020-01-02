#include "Graphics.h"
#include "Util.h"

#include "d2d1_1helper.h"
#include "d3d11.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d2d1.lib")

#ifdef _DEBUG
constexpr const UINT deviceFlags = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#else
constexpr const UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif // _DEBUG

constexpr const DXGI_SWAP_CHAIN_DESC defaultSwapChainDesc = {
	{										// BufferDesc:
		0u,										// Width
		0u,										// Height
		{										// RefreshRate:
			60u,									// Numerator
			1u										// Denominator
		},
		DXGI_FORMAT_B8G8R8A8_UNORM,				// Format
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,	// ScanlineOrdering
		DXGI_MODE_SCALING_UNSPECIFIED			// Scaling
	},
	{										// SampleDesc:
		1u,										// Count
		0u										// Quality
	},
	DXGI_USAGE_RENDER_TARGET_OUTPUT,		// BufferUsage
	2u,										// BufferCount
	NULL,									// OutputWindow
	TRUE,									// Windowed
	DXGI_SWAP_EFFECT_DISCARD,				// SwapEffect
	DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH	// Flags
};

constexpr const D3D11_DEPTH_STENCIL_DESC defaultDepthStencilDesc = {
	TRUE,								// DepthEnabled
	D3D11_DEPTH_WRITE_MASK_ALL,			// DepthWriteMask
	D3D11_COMPARISON_LESS,				// DepthFunc
	FALSE,								// StencilEnable
	D3D11_DEFAULT_STENCIL_READ_MASK,	// StencilReadMask
	D3D11_DEFAULT_STENCIL_WRITE_MASK,	// StencilWriteMask
	{									// FrontFace:

		D3D11_STENCIL_OP_KEEP,				// StencilFailOp
		D3D11_STENCIL_OP_KEEP,				// StencilDepthFailOp
		D3D11_STENCIL_OP_KEEP,				// StencilPassOp
		D3D11_COMPARISON_ALWAYS				// StencilFunc
	},
	{									// BackFace:

		D3D11_STENCIL_OP_KEEP,				// StencilFailOp
		D3D11_STENCIL_OP_KEEP,				// StencilDepthFailOp
		D3D11_STENCIL_OP_KEEP,				// StencilPassOp
		D3D11_COMPARISON_ALWAYS				// StencilFunc
	}
};

constexpr const D3D11_TEXTURE2D_DESC defaultDepthStencilBufferDesc = {
	0u,							// Width
	0u,							// Height
	1u,							// MipLevels
	1u,							// ArraySize
	DXGI_FORMAT_D32_FLOAT,		// Format
	{							// SampleDesc:
		1u,							// Count
		0u							// Quality
	},
	D3D11_USAGE_DEFAULT,		// Usage
	D3D11_BIND_DEPTH_STENCIL,	// BindFlags
	0u,							// CPUAccessFlags
	0u							// MiscFlags
};

constexpr const D3D11_DEPTH_STENCIL_VIEW_DESC defaultDepthStencilViewDesc = {
	DXGI_FORMAT_D32_FLOAT,			// Format
	D3D11_DSV_DIMENSION_TEXTURE2D,	// ViewDimension
	0u,								// Flags
	0u								// Texture2D.MipSlice
};

// Graphics
Graphics::Graphics(HWND hWnd ) {
	
	DXGI_SWAP_CHAIN_DESC sd = defaultSwapChainDesc;
	sd.OutputWindow = hWnd;

	const D3D_FEATURE_LEVEL fl[] = {
		D3D_FEATURE_LEVEL_11_1
	};

	ThrowIfFailed( D2D1CreateFactory<ID2D1Factory1>( D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory2D ) );
	
	ThrowIfFailed( D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceFlags, fl, 1, D3D11_SDK_VERSION, &sd, 
												  &pSwap, &pDevice, NULL, &pContext) );

	Microsoft::WRL::ComPtr<IDXGIDevice> pDeviceDXGI;

	ThrowIfFailed( pDevice.As(&pDeviceDXGI) );
	ThrowIfFailed( pFactory2D->CreateDevice( pDeviceDXGI.Get(), &pDevice2D ) );
	ThrowIfFailed( pDevice2D->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &pContext2D ) );

	blendState.Init( pDevice.Get() );
	depthState.Init( pDevice.Get() );
}

Graphics::~Graphics() {

#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug> pDebug;
	pDevice.As( &pDebug );
#endif // _DEBUG

	pDevice.Reset();
	pSwap.Reset();
	pContext.Reset();
	pRTV.Reset();
	pDSV.Reset();

#ifdef _DEBUG
	pDebug->ReportLiveDeviceObjects( D3D11_RLDO_DETAIL );
#endif // _DEBUG

}

void Graphics::SizeChanged() {

	// drop render target view
	pRTV.Reset();
	pContext->OMSetRenderTargets(0, NULL, NULL);

	// drop target bitmap
	pBitmapTarget2D.Reset();
	pContext2D->SetTarget( NULL );

	// resize buffers
	ThrowIfFailed( pSwap->ResizeBuffers( 0, 0, 0, DXGI_FORMAT_UNKNOWN, 0 ) );

	Microsoft::WRL::ComPtr<ID3D11Resource> pBB;
	ThrowIfFailed( pSwap->GetBuffer( 0u, __uuidof(ID3D11Resource), &pBB ) ); // get the swapchains first backbuffer
	ThrowIfFailed( pDevice->CreateRenderTargetView( pBB.Get(), nullptr, &pRTV ) ); // create rtv of it and store the interface in pRTV
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDS; // pointer to texture holding depth and stencil info

	DXGI_SWAP_CHAIN_DESC sd;
	pSwap->GetDesc( &sd );
	D3D11_TEXTURE2D_DESC dsbd = defaultDepthStencilBufferDesc;
	dsbd.Width = sd.BufferDesc.Width;
	dsbd.Height = sd.BufferDesc.Height;

	pDevice->CreateTexture2D( &dsbd, nullptr, &pDS ); // create depth stencil buffer

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = defaultDepthStencilViewDesc;

	pDevice->CreateDepthStencilView( pDS.Get(), &dsvd, &pDSV ); // create view of depth stencil buffer
	
	pContext->OMSetRenderTargets( 1u, pRTV.GetAddressOf(), pDSV.Get() ); // bind render target and depth stencil buffers to output merger

		// create and set viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(sd.BufferDesc.Width);
	vp.Height = static_cast<float>(sd.BufferDesc.Height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	
	pContext->RSSetViewports( 1u, &vp );

	D2D1_BITMAP_PROPERTIES1 bmp;
	ZeroMemory( &bmp, sizeof( bmp ) );
	bmp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bmp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	pFactory2D->GetDesktopDpi( &bmp.dpiX, &bmp.dpiY );
	bmp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

	Microsoft::WRL::ComPtr<IDXGISurface> pBBDXGI;

	ThrowIfFailed( pSwap->GetBuffer( 0u, __uuidof(IDXGISurface), &pBBDXGI ) );
	ThrowIfFailed( pContext2D->CreateBitmapFromDxgiSurface( pBBDXGI.Get(), &bmp, &pBitmapTarget2D ) );
	pContext2D->SetTarget( pBitmapTarget2D.Get() );

}

void Graphics::Clear( float r, float g, float b ) const {

	const float rgba[4] = {
		r, g, b, 1.0f
	};

	pContext->ClearRenderTargetView( pRTV.Get(), rgba );
	pContext->ClearDepthStencilView( pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u );
}

void Graphics::Clear( const float* rgba ) const {
	pContext->ClearRenderTargetView( pRTV.Get(), rgba );
	pContext->ClearDepthStencilView( pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u );
}

void Graphics::Present() const {
	ThrowIfFailed( pSwap->Present( 1u, 0u ) );
}

void Graphics::SetDepthEnabled( bool enable ) const {
	depthState.Enabled( enable );
}

void Graphics::SetBlendEnabled( bool enable ) const {
	blendState.Enabled( enable );
}

ID3D11Device* Graphics::GetDevice() const {
	return pDevice.Get();
}

ID3D11DeviceContext* Graphics::GetContext() const {
	return pContext.Get();
}

ID2D1DeviceContext* Graphics::GetContext2D() const {
	return pContext2D.Get();
}

D2D1_SIZE_U Graphics::GetTargetSize() const {
	return pBitmapTarget2D->GetPixelSize();
}
