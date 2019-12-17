#pragma once

#include "ConstantBuffer.h"
#include "D3DCompiler.h"

#define DEFAULT_SHADER_DECL( Type, Char ) class Type##Shader : public Bindable {\
public:\
	Type##Shader( std::string name );\
	void Bind() override;\
private:\
	Microsoft::WRL::ComPtr<ID3D11##Type##Shader> p##Type##Shader; \
};\

DEFAULT_SHADER_DECL(Pixel, P)
DEFAULT_SHADER_DECL(Geometry, G)

#undef DEFAULT_SHADER_DECL


class VertexShader : public Bindable {

public:
	VertexShader( std::string name );
	void Bind() override;
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};

