#include "Graphics.h"
#include "Util.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Graphics::Graphics(HWND hWnd) {
	
	// create swap chain descriptor
	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.OutputWindow = hWnd;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2; // use 1 backbuffer and 1 frontbuffer
	sd.Flags = 0u; // no flags

	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60; // Refreshrate is set to 0/0 to indicate that it should be same as monitors
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count = 1; // no anti aliasing
	sd.SampleDesc.Quality = 0;

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
		NULL,						// dont care about what featurelevel d3d11 ended up using.
									//On modern hardware we can assume at least D3D_FEATURE_LEVEL_11_0.
		&pContext
	) );
	
	// create RenderTargetView
	Microsoft::WRL::ComPtr<ID3D11Resource> pBB;
	ThrowIfFailed( pSwap->GetBuffer( 0u, __uuidof(ID3D11Resource), &pBB ) ); // Get the swapchains first backbuffer
	ThrowIfFailed( pDevice->CreateRenderTargetView( pBB.Get(), nullptr, &pRTV ) ); // Create RT view of it and store the interface in pRTV
}
