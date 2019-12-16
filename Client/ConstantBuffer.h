#pragma once

#include "Bindable.h"
#include "WRL.h"
#include "d3d11.h"

#include "Window.h"
#include "Util.h"

constexpr const D3D11_BUFFER_DESC defaultConstantBufferDesc = {
	0u,							// ByteWidth
	D3D11_USAGE_DYNAMIC,		// Usage
	D3D11_BIND_CONSTANT_BUFFER,	// BindFlags
	D3D11_CPU_ACCESS_WRITE,		// CPUAccessFlags
	0u,							// MiscFlags
	0u,							// StructureByteStride
};

enum Stage {
	VS, PS
};

template<typename T, Stage S, unsigned char slot>
class ConstantBuffer : public Bindable { 
	
public:
	ConstantBuffer( const T* init );

	void Set( const T* to );
	void Bind() override;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;

};


template<typename T, Stage S, unsigned char slot>
ConstantBuffer<T, S, slot>::ConstantBuffer( const T* init ) {

	D3D11_BUFFER_DESC bd = defaultConstantBufferDesc;
	bd.ByteWidth = sizeof( T );

	D3D11_SUBRESOURCE_DATA sd = { };
	sd.pSysMem = init;

	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateBuffer( &bd, &sd, &pBuffer ) );

}

template<typename T, Stage S, unsigned char slot>
void ConstantBuffer<T, S, slot>::Set( const T* from ) {
	
	D3D11_MAPPED_SUBRESOURCE msr = { 0 };
	Window::Get().GetGraphics().GetContext()->Map( pBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr );

	memcpy( msr.pData, from, sizeof( T ) );

	Window::Get().GetGraphics().GetContext()->Unmap( pBuffer.Get(), 0u );
}

template<typename T, Stage S, unsigned char slot>
void ConstantBuffer<T, S, slot>::Bind() {
	
	switch ( S ) {
	case VS:
		Window::Get().GetGraphics().GetContext()->VSSetConstantBuffers( slot, 1u, pBuffer.GetAddressOf() );
		break;
	case PS:
		Window::Get().GetGraphics().GetContext()->PSSetConstantBuffers( slot, 1u, pBuffer.GetAddressOf() );
		break;

	}
}
