#include "Shader.h"

GeometryShader::GeometryShader( std::string name ) {
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	std::wstring path = std::wstring{ name.begin(), name.end() } +L".cso";
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> pGS;
	ThrowIfFailed( D3DReadFileToBlob( path.c_str(), &pBlob ) );

	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->CreateGeometryShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pGShader ) );
}

void GeometryShader::Bind() {
	Window::Get().GetGraphics().GetContext()->GSSetShader( pGShader.Get(), NULL, 0u );
}
