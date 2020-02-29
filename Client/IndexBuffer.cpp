#include "IndexBuffer.h"
#include "Util.h"
#include "Window.h"

#include "d3d11_2.h"

constexpr const D3D11_BUFFER_DESC defaultIndexBufferDesc = {
	0u,							// ByteWidth
	D3D11_USAGE_DEFAULT,		// Usage
	D3D11_BIND_INDEX_BUFFER,	// BindFlags
	0u,							// CPUAccessFlags
	0u,							// MiscFlags
	sizeof( uint16_t )	// StructureByteStride
};

IndexBuffer::IndexBuffer( const uint16_t* indices, size_t size ) : size(size) {

	D3D11_BUFFER_DESC bd = defaultIndexBufferDesc;
	bd.ByteWidth = (UINT) (sizeof( uint16_t ) * size);

	D3D11_SUBRESOURCE_DATA sd = { };
	sd.pSysMem = indices;

	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateBuffer( &bd, &sd, &pBuffer ) );

#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D11DeviceChild> pChild;
	pBuffer.As( &pChild );
	pChild->SetPrivateData( WKPDID_D3DDebugObjectName, 11, "IndexBuffer" );
#endif // _DEBUG
}

void IndexBuffer::Bind() {
	Window::Get().GetGraphics().GetContext()->IASetIndexBuffer( pBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u );
}

size_t IndexBuffer::GetSize() const {
	return size;
}


