#pragma once

struct ID3D11Device1; 
struct ID3D11DeviceContext;
struct IDXGISwapChain1;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

#include "States.h"

#include "dwrite_1.h"
#include "d2d1_1.h"
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
	void Clear( float r, float g, float b ) const;
	void Clear( const float* rgba ) const;

	// displays currently drawn frame
	void Present() const;

	// setter for using depth or not
	void SetDepthEnabled( bool enable ) const;
	// setter for using alpha blending or not
	void SetBlendEnabled( bool enable ) const;

	// getters for DX11 interfaces
	ID3D11Device1* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	ID2D1Device* GetDevice2D() const;
	ID2D1DeviceContext* GetContext2D() const;
	ID2D1Bitmap1* GetTarget2D() const;
	IDWriteFactory* GetWriteFactory() const;

	// other getters
	D2D1_SIZE_U GetTargetSize() const;
	D2D1_SIZE_F GetTargetDipSize() const;
	float GetDpiXScale() const;
	float GetDpiYScale() const;

private:
	// 3D
	Microsoft::WRL::ComPtr<ID3D11Device1> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;

	// 2D
	Microsoft::WRL::ComPtr<ID2D1Device> pDevice2D;
	Microsoft::WRL::ComPtr<ID2D1DeviceContext> pContext2D;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> pBitmapTarget2D;

	// Write
	Microsoft::WRL::ComPtr<IDWriteFactory1> pWriteFactory;

	BlendState blendState;
	DepthState depthState;

	float dpiScaleX, dpiScaleY;
};

