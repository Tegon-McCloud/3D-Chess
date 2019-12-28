#pragma once

#include "Bindable.h"

#include "d3d11.h"
#include "WRL.h"
#include <string>


class VertexShader : public Bindable {

public:
	VertexShader( std::string name );
	void Bind() override;
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};

class GeometryShader : public Bindable {

public:
	GeometryShader( std::string name );
	void Bind() override;
private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> pGeometryShader;
	D3D11_PRIMITIVE_TOPOLOGY topology;
};

class PixelShader : public Bindable {

public:
	PixelShader( std::string name );
	void Bind() override;
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

};