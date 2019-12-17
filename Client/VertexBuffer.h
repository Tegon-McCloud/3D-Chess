#pragma once

#include "Bindable.h"
#include "WRL.h"
#include "d3d11.h"
#include <unordered_map>
#include <string>


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

