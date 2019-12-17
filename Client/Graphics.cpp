#include "Graphics.h"
#include "Util.h"
#include "Window.h"
#include "d3dcompiler.h"
#include "DirectXMath.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "Camera.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#ifdef _DEBUG
constexpr const UINT deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
constexpr const UINT deviceFlags = 0u;
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
	D3D11_COMPARISON_LESS_EQUAL,		// DepthFunc
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

	ThrowIfFailed( D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceFlags, NULL, 0, D3D11_SDK_VERSION, &sd, 
												  &pSwap, &pDevice, NULL, &pContext) );
}

void Graphics::SizeChanged() {

	// drop render target view
	pRTV.Reset();
	pContext->OMSetRenderTargets(0, NULL, NULL);

	// resize buffers
	ThrowIfFailed(pSwap->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));

	Microsoft::WRL::ComPtr<ID3D11Resource> pBB;
	ThrowIfFailed( pSwap->GetBuffer( 0u, __uuidof(ID3D11Resource), &pBB ) ); // get the swapchains first backbuffer
	ThrowIfFailed( pDevice->CreateRenderTargetView( pBB.Get(), nullptr, &pRTV ) ); // create rtv of it and store the interface in pRTV
	
	// create and bind depth stencil state to output merger
	D3D11_DEPTH_STENCIL_DESC dsd = defaultDepthStencilDesc;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSS;
	pDevice->CreateDepthStencilState( &dsd, &pDSS );
	pContext->OMSetDepthStencilState( pDSS.Get(), 1u );

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDS; // pointer to texture holding depth and stencil info

	DXGI_SWAP_CHAIN_DESC sd;
	pSwap->GetDesc( &sd );
	D3D11_TEXTURE2D_DESC dsbd = defaultDepthStencilBufferDesc;
	dsbd.Width = sd.BufferDesc.Width;
	dsbd.Height = sd.BufferDesc.Height;

	pDevice->CreateTexture2D( &dsbd, nullptr, &pDS ); // create depth stencil buffer

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = defaultDepthStencilViewDesc;

	pDevice->CreateDepthStencilView( pDS.Get(), &dsvd, &pDSV ); // create view of depth stencil buffer
	
	pContext->OMSetRenderTargets( 1u, pRTV.GetAddressOf(), NULL ); // bind render target and depth stencil buffers to output merger

		// create and set viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(sd.BufferDesc.Width);
	vp.Height = static_cast<float>(sd.BufferDesc.Height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	
	pContext->RSSetViewports( 1u, &vp );


}

void Graphics::Clear( const float& r, const float& g, const float& b ) const {

	const float rgba[4] = {
		r, g, b, 1.0f
	};

	pContext->ClearRenderTargetView( pRTV.Get(), rgba );
	pContext->ClearDepthStencilView( pDSV.Get(), D3D11_CLEAR_DEPTH, 0.0f, 0u );
}

void Graphics::Clear( const float* rgba ) const {
	pContext->ClearRenderTargetView( pRTV.Get(), rgba );
	pContext->ClearDepthStencilView( pDSV.Get(), D3D11_CLEAR_DEPTH, 0.0f, 0u );
}

void Graphics::DrawTest() const {

	using namespace DirectX;

	Camera c(0.0f, 2.0f, -4.0f, 0.5f, 0.0f, 0.0f);
	c.UpdateBuffer();
	c.Bind();

	// =============== BUFFERS ===============

	// create vertex buffer

	const Vertex vertices[] = {
		{ -1.0f, -1.0f, -1.0f },
		{ +1.0f, -1.0f, -1.0f },
		{ +1.0f, +1.0f, -1.0f },
		{ -1.0f, +1.0f, -1.0f },
		{ -1.0f, -1.0f, +1.0f },
		{ +1.0f, -1.0f, +1.0f },
		{ +1.0f, +1.0f, +1.0f },
		{ -1.0f, +1.0f, +1.0f },
	};

	
	VertexBuffer vb( vertices, std::size( vertices ) );
	vb.Bind();

	// create index buffer
	const unsigned short indices[]{
		0, 3, 1,	3, 2, 1,
		1, 2, 5,	2, 6, 5,
		5, 6, 4,	6, 7, 4,
		4, 7, 0,	7, 3, 0,
		3, 7, 2,	7, 6, 2,
		4, 0, 5,	0, 1, 5
	};
	
	IndexBuffer ib( indices, std::size( indices ) );
	ib.Bind();

	//create constant buffer
	const XMMATRIX transform =
		XMMatrixTranspose(
			DirectX::XMMatrixRotationZ( 1.0f )
			//XMMatrixIdentity()
		);

	ConstantBuffer<XMMATRIX, VS, 0> cb;
	cb.Set( &transform );
	cb.Bind();

	// =============== SHADERS ===============
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

	// load vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVS;

	ThrowIfFailed( D3DReadFileToBlob( L"VertexShader.cso", &pBlob ) );
	ThrowIfFailed( pDevice->CreateVertexShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pVS ) );

	// bind vertex shader
	pContext->VSSetShader( pVS.Get(), NULL, 0u );

	// vertex layout
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pIL;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	
	ThrowIfFailed( pDevice->CreateInputLayout( ied, 1u, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pIL ) );

	pContext->IASetInputLayout( pIL.Get() );


	// load pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPS;

	ThrowIfFailed( D3DReadFileToBlob( L"PixelShader.cso", &pBlob ) );
	ThrowIfFailed( pDevice->CreatePixelShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pPS ) );

	// bind pixel shader
	pContext->PSSetShader( pPS.Get(), NULL, 0u );

	// load geometry shader
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> pGS;
	ThrowIfFailed( D3DReadFileToBlob( L"GeometryShader.cso", &pBlob ) );
	ThrowIfFailed( pDevice->CreateGeometryShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pGS ) );

	// bind geometry shader
	pContext->GSSetShader( pGS.Get(), NULL, 0u );


	// set primitive topology
	pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// draw
	pContext->DrawIndexed( ib.GetSize(), 0u, 0u );

}

void Graphics::Present() const {

	ThrowIfFailed( pSwap->Present( 1u, 0u ) );
}

ID3D11Device* Graphics::GetDevice() const {
	return pDevice.Get();
}

ID3D11DeviceContext* Graphics::GetContext() const {
	return pContext.Get();
}
