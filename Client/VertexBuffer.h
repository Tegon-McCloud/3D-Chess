#pragma once

struct ID3D11Buffer;

#include "Bindable.h"

#include "WRL.h"

struct Vertex {
	float x, y, z;
};

class VertexBuffer : public Bindable {

public:
	VertexBuffer( const Vertex* vertices, size_t size );
	VertexBuffer() = delete;

	void Bind() override;

private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
};

