#pragma once
#include <stdint.h>

struct ID3D11Buffer;

#include "Bindable.h"

#include "WRL.h"

class IndexBuffer : public Bindable {
	
public:
	IndexBuffer( const uint16_t * indices, size_t size);
	IndexBuffer() = delete;

	void Bind() override;
	size_t GetSize() const;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
	size_t size;
};

