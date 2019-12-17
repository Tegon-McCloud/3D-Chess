#include "IndexBuffer.h"
#include "Util.h"
#include "Window.h"

constexpr const D3D11_BUFFER_DESC defaultIndexBufferDesc = {
	0u,							// ByteWidth
	D3D11_USAGE_DEFAULT,		// Usage
	D3D11_BIND_INDEX_BUFFER,	// BindFlags
	0u,							// CPUAccessFlags
	0u,							// MiscFlags
	sizeof( unsigned short )	// StructureByteStride
};

IndexBuffer::IndexBuffer( const unsigned short* indices, size_t size, std::string tag ) {

	if ( !tag.empty() ) {
		auto it = GetCodex().find( tag );
		
		if ( it != GetCodex().end() ) {
			pBuffer = it->second;

			return;
		}

	} 

	D3D11_BUFFER_DESC bd = defaultIndexBufferDesc;
	bd.ByteWidth = sizeof( unsigned short ) * size;

	D3D11_SUBRESOURCE_DATA sd = { };
	sd.pSysMem = indices;

	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateBuffer( &bd, &sd, &pBuffer ) );

	if ( !tag.empty() ) {
		GetCodex()[tag] = pBuffer;
	}

}

void IndexBuffer::Bind() {
	Window::Get().GetGraphics().GetContext()->IASetIndexBuffer( pBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u );
}

size_t IndexBuffer::GetSize() const {
	D3D11_BUFFER_DESC bd;
	pBuffer->GetDesc( &bd );
	return bd.ByteWidth / sizeof( unsigned short );
}

