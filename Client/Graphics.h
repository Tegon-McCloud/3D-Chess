#pragma once

#include "WRL.h"
#include "d3d11.h"

// graphics is owned by a Window and is responsible for communicating with DX11
class Graphics {

	friend class Window;

private:
	Graphics() = default;
	Graphics( HWND hWnd );

	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;

	void SizeChanged();

public:
	void Clear( const float& r, const float& g, const float& b ) const;
	void Clear( const float* rgba ) const;
	void DrawTest() const;
	void Present() const;

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;

};

