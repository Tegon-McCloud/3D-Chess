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
	VertexBuffer( const Vertex* vertices, size_t size, std::string tag = "" );
	VertexBuffer() = delete;

	void Bind() override;

private:
	static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>>& GetCodex() {
		static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>> codex; // lib will hold all tagged IndexBuffers
		return codex;
	}

	static void CleanCodex();

	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
};

