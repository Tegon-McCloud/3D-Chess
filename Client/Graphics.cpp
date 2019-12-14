#include "Graphics.h"
#include "Util.h"
#include "Window.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

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
	0u										// Flags
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

Graphics::Graphics(HWND hWnd, int width, int height, bool isWindowed) {
	
	DXGI_SWAP_CHAIN_DESC sd = defaultSwapChainDesc;
	sd.OutputWindow = hWnd;
	sd.Windowed = isWindowed;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;

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
	D3D11_DEPTH_STENCIL_DESC dsd = defaultDepthStencilDesc;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSS;
	pDevice->CreateDepthStencilState( &dsd, &pDSS );
	pContext->OMSetDepthStencilState( pDSS.Get(), 1u );

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDS; // pointer to texture holding depth and stencil info

	D3D11_TEXTURE2D_DESC dsbd = defaultDepthStencilBufferDesc;
	dsbd.Width = width;
	dsbd.Height = height;

	pDevice->CreateTexture2D( &dsbd, nullptr, &pDS ); // create depth stencil buffer

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = defaultDepthStencilViewDesc;

	pDevice->CreateDepthStencilView( pDS.Get(), &dsvd, &pDSV ); // create view of depth stencil buffer

	pContext->OMSetRenderTargets( 1u, pRTV.GetAddressOf(), pDSV.Get() ); // bind render target and depth stencil buffers to output merger
	
}

void Graphics::Clear( float r, float g, float b ) const {

	const float rgba[4] = {
		r, g, b, 1.0f
	};

	pContext->ClearRenderTargetView( pRTV.Get(), rgba );
	pContext->ClearDepthStencilView( pDSV.Get(), D3D11_CLEAR_DEPTH, 0.0f, 0u );
}

void Graphics::Present() const {
	ThrowIfFailed( pSwap->Present( 1u, 0u ) );
}
