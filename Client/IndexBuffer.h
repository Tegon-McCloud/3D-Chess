#pragma once

#include "Bindable.h"

#include "WRL.h"
#include "d3d11.h"
#include <unordered_map>
#include <string>

class IndexBuffer : public Bindable {
	
public:
	IndexBuffer( const unsigned short* indices, size_t size);
	IndexBuffer() = delete;

	void Bind() override;
	size_t GetSize() const;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
	size_t size;
};

