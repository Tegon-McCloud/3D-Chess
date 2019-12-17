#include "Shaders.h"

VertexShader::VertexShader( std::string name ) {
	
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	std::wstring path = std::wstring{ name.begin(), name.end() } +L".cso";
	ThrowIfFailed( D3DReadFileToBlob( path.c_str(), &pBlob ) );
	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateVertexShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pVertexShader ) );

	const D3D11_INPUT_ELEMENT_DESC ied = { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateInputLayout( &ied, 1u, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout ) );
}

void VertexShader::Bind() {
	Window::Get().GetGraphics().GetContext()->VSSetShader( pVertexShader.Get(), NULL, 0u );
	Window::Get().GetGraphics().GetContext()->IASetInputLayout( pInputLayout.Get() );
}

GeometryShader::GeometryShader( std::string name ) {
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	std::wstring path = std::wstring{ name.begin(), name.end() } +L".cso";
	ThrowIfFailed( D3DReadFileToBlob( path.c_str(), &pBlob ) );
	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateGeometryShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pGeometryShader ) );

	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

void GeometryShader::Bind() {
	Window::Get().GetGraphics().GetContext()->GSSetShader( pGeometryShader.Get(), NULL, 0u );
	Window::Get().GetGraphics().GetContext()->IASetPrimitiveTopology( topology );
}

PixelShader::PixelShader( std::string name ) {
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	std::wstring path = std::wstring{ name.begin(), name.end() } +L".cso";
	ThrowIfFailed( D3DReadFileToBlob( path.c_str(), &pBlob ) );
	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreatePixelShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pPixelShader ) );
}

void PixelShader::Bind() {
	Window::Get().GetGraphics().GetContext()->PSSetShader( pPixelShader.Get(), NULL, 0u );
}
