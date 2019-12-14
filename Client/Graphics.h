#pragma once

#include "WRL.h"
#include "d3d11.h"

// graphics is owned by a Window and is responsible for communicating with DX11
class Graphics {

	friend class Window;
	
public:
	void Clear( float r, float g, float b ) const;
	void Present() const;


private:
	Graphics() = default;
	Graphics( HWND hWnd, int width, int height, bool isWindowed );


private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};

