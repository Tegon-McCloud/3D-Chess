#pragma once

#include "ConstantBuffer.h"
#include "D3DCompiler.h"

class GeometryShader : public Bindable {

public:
	GeometryShader( std::string name );
	
	void Bind() override;

private:

	Microsoft::WRL::ComPtr<ID3D11GeometryShader> pGShader;

};



