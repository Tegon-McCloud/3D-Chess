#include "VertexBuffer.h"
#include "Util.h"
#include "Window.h"

constexpr const D3D11_BUFFER_DESC defaultVertexBufferDesc = {
	0u,							// ByteWidth
	D3D11_USAGE_DEFAULT,		// Usage
	D3D11_BIND_VERTEX_BUFFER,	// BindFlags
	0u,							// CPUAccessFlags
	0u,							// MiscFlags
	sizeof( Vertex )			// StructureByteStride
};

VertexBuffer::VertexBuffer( const Vertex* vertices, size_t size ) {

	D3D11_BUFFER_DESC bd = defaultVertexBufferDesc;
	bd.ByteWidth = (UINT) (sizeof( Vertex ) * size);

	D3D11_SUBRESOURCE_DATA sd = { };
	sd.pSysMem = vertices;

	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateBuffer( &bd, &sd, &pBuffer ) );

#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D11DeviceChild> pChild;
	pBuffer.As( &pChild );
	pChild->SetPrivateData( WKPDID_D3DDebugObjectName, 12, "VertexBuffer" );
#endif // !_DEBUG
}

void VertexBuffer::Bind() {
	const UINT stride = sizeof( Vertex );
	const UINT offset = 0u;
	Window::Get().GetGraphics().GetContext()->IASetVertexBuffers( 0u, 1u, pBuffer.GetAddressOf(), &stride, &offset );
}

