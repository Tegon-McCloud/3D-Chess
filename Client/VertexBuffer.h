#pragma once

struct ID3D11Buffer;

#include "Bindable.h"

#include "WRL.h"

typedef struct {
	float x, y, z;
} Vertex;

class VertexBuffer : public Bindable {

public:
	VertexBuffer( const Vertex* vertices, size_t size );
	VertexBuffer() = delete;

	void Bind() override;

private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
};

