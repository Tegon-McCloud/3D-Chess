#include "Shaders.h"

#define DEFAULT_SHADER_IMPL( Type, Char ) Type##Shader::##Type##Shader( std::string name ) {\
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;\
	std::wstring path = std::wstring{ name.begin(), name.end() } +L".cso";\
	ThrowIfFailed( D3DReadFileToBlob( path.c_str(), &pBlob ) );\
	ThrowIfFailed( Window::Get().GetGraphics().GetDevice()->Create##Type##Shader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &p##Type##Shader ) );\
}\
void Type##Shader::Bind() {\
	Window::Get().GetGraphics().GetContext()->##Char##SSetShader( p##Type##Shader.Get(), NULL, 0u );\
}\

DEFAULT_SHADER_IMPL( Pixel, P );
DEFAULT_SHADER_IMPL( Geometry, G );

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
