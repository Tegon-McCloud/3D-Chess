#pragma once

struct ID3D11Device; 
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

#include "States.h"

#include "WRL.h"

/* The Graphics type, is instantiated by the Window on creation.
 * It manages the DX11 pipeline.
 */
class Graphics {

	friend class Window;

private:
	// private constructors so only Window can use
	Graphics( HWND hWnd );	// this constructor will initialize a graphics pipeline
	~Graphics();

	// no copying
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	
	// called by window, will resize target buffers
	void SizeChanged();

public:
	// clears render target and depth stencil buffer
	void Clear( const float& r, const float& g, const float& b ) const;
	void Clear( const float* rgba ) const;

	// displays currently drawn frame
	void Present() const;

	// setter for using depth or not
	void SetDepthEnabled( bool enable ) const;
	// setter for using alpha blending or not
	void SetBlendEnabled( bool enable ) const;

	// getters for DX11 interfaces
	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;

	BlendState blendState;
	DepthState depthState;
};

